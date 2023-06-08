# Project Title

Audio Relay on ESP32

## Project Description

This project aims to create a functional audio relay on the ESP32 (DOIT ESP32 DevKitV1) using the Espressif framework and FreeRTOS. The goal is to receive compressed audio data from a UDP server client, decompress it, and push it to the DMA controller. The DMA controller then sends the data to the DAC, which plays the audio.

## Features

- Connects to Wi-Fi in power save mode
- Indication of a connection through a LED
- UDP server that can receive data from clients

## License

This project is licensed under the [MIT License](LICENSE).
