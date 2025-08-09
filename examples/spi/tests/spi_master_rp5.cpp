// spi_master_rp5.cpp
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cerrno>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

static const char *SPI_DEVICE = "/dev/spidev0.0";
static const uint8_t SPI_MODE = SPI_MODE_0;
static const uint8_t SPI_BITS = 8;
static const uint32_t SPI_SPEED = 1000000; // 1 MHz (ajusta si quieres)
static const int HANDSHAKE_GPIO = 17; // BCM pin en la RPi que vas a conectar a GPIO_HANDSHAKE del ESP32
static const int TRANSFER_SIZE = 128; // bytes (coincide con el ESP32)

bool gpio_export(int gpio) {
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0) {
        if (errno == EACCES) perror("export open");
        return false;
    }
    char buf[32];
    int l = snprintf(buf, sizeof(buf), "%d", gpio);
    if (write(fd, buf, l) != l) {
        if (errno != EBUSY) { perror("export write"); close(fd); return false; }
    }
    close(fd);
    return true;
}

bool gpio_set_dir_in(int gpio) {
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", gpio);
    int fd = open(path, O_WRONLY);
    if (fd < 0) { perror("open direction"); return false; }
    if (write(fd, "in", 2) != 2) { perror("write direction"); close(fd); return false; }
    close(fd);
    return true;
}

int gpio_get_value(int gpio) {
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", gpio);
    int fd = open(path, O_RDONLY);
    if (fd < 0) { return -1; }
    char v;
    if (read(fd, &v, 1) != 1) { close(fd); return -1; }
    close(fd);
    return (v == '1') ? 1 : 0;
}

int main() {
    // Requiere permisos (sudo) para /dev/spidev0.0 y /sys/class/gpio
    printf("SPI master RP5 test - device %s, handshake GPIO %d\n", SPI_DEVICE, HANDSHAKE_GPIO);

    // Exportar y configurar GPIO handshake como entrada
    gpio_export(HANDSHAKE_GPIO);
    gpio_set_dir_in(HANDSHAKE_GPIO);

    // Abrir dispositivo SPI
    int fd = open(SPI_DEVICE, O_RDWR);
    if (fd < 0) { perror("open spidev"); return 1; }

    // Configurar modo, bits y velocidad
    if (ioctl(fd, SPI_IOC_WR_MODE, &SPI_MODE) < 0) { perror("SPI set mode"); close(fd); return 1; }
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &SPI_BITS) < 0) { perror("SPI set bits"); close(fd); return 1; }
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPI_SPEED) < 0) { perror("SPI set speed"); close(fd); return 1; }

    printf("SPI configured: mode %u bits %u speed %u Hz\n", SPI_MODE, SPI_BITS, SPI_SPEED);

    uint8_t txbuf[TRANSFER_SIZE];
    uint8_t rxbuf[TRANSFER_SIZE];

    // Loop principal: esperar handshake -> transferir 128 bytes -> imprimir rx
    for (int cycle = 0; cycle < 1000; ++cycle) {
        // Esperar handshake (con timeout sencillo)
        const int max_wait_ms = 5000;
        int waited = 0;
        while (1) {
            int v = gpio_get_value(HANDSHAKE_GPIO);
            if (v == 1) break;
            usleep(10000); // 10 ms
            waited += 10;
            if (waited >= max_wait_ms) {
                printf("Timeout esperando handshake (intento %d). Reintentando...\n", cycle);
                break; // volver a esperar otra vez
            }
        }

        // Preparar TX: aquí envías datos al ESP32 (lo que el ESP32 recibirá en recvbuf)
        memset(txbuf, 0x55, TRANSFER_SIZE);
        // ejemplo: escribir un contador ASCII al inicio
        char header[64];
        snprintf(header, sizeof(header), "Master sending cycle %04d", cycle);
        size_t hlen = strlen(header);
        if (hlen > (size_t)TRANSFER_SIZE) hlen = TRANSFER_SIZE;
        memcpy(txbuf, header, hlen);

        memset(rxbuf, 0, TRANSFER_SIZE);

        struct spi_ioc_transfer tr;
        memset(&tr, 0, sizeof(tr));
        tr.tx_buf = (unsigned long)txbuf;
        tr.rx_buf = (unsigned long)rxbuf;
        tr.len = TRANSFER_SIZE;
        tr.speed_hz = SPI_SPEED;
        tr.bits_per_word = SPI_BITS;
        tr.delay_usecs = 0;

        int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
        if (ret < 1) {
            perror("SPI transfer failed");
            // si falla, espera un poco y sigue
            usleep(200000);
            continue;
        }

        // Imprimir lo que recibimos del esclavo (ESP32)
        // Termina en cero si el ESP32 puso una cadena C; hacemos protección
        rxbuf[TRANSFER_SIZE-1] = 0;
        printf("Cycle %d - Received from slave: %s\n", cycle, (char*)rxbuf);

        // Pequeña pausa antes del siguiente ciclo
        usleep(200000);
    }

    close(fd);
    return 0;
}
