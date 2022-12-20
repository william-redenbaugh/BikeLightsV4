#include "bluetooth_interface_module.h"
#include "Particle.h"


// This example does not require the cloud so you can run it in manual mode or
// normal cloud-connected mode
// SYSTEM_MODE(MANUAL);

const size_t UART_TX_BUF_SIZE = 20;

static void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context);
static void update_battery_level_ble(void);
// These UUIDs were defined by Nordic Semiconductor and are now the defacto standard for
// UART-like services over BLE. Many apps support the UUIDs now, like the Adafruit Bluefruit app.
const BleUuid serviceUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid rxUuid("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid txUuid("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY, txUuid, serviceUuid);
BleCharacteristic rxCharacteristic("rx", BleCharacteristicProperty::WRITE_WO_RSP, rxUuid, serviceUuid, onDataReceived, NULL);

// The battery level service allows the battery level to be monitored
const BleUuid batteryLevelService(0x180f);

// The battery_level characteristic shows the battery level of
BleCharacteristic batteryLevelCharacteristic("bat", BleCharacteristicProperty::NOTIFY, BleUuid(0x2A19), batteryLevelService);
Timer battery_ble_update_timer(3000, update_battery_level_ble);

void update_battery_level_ble(void){
    FuelGauge fuel;
    float battery_level = fuel.getVCell();
    
    batteryLevelCharacteristic.setValue((const char*)&battery_level);
}

void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context) {
    // Log.trace("Received data from: %02X:%02X:%02X:%02X:%02X:%02X:", peer.address()[0], peer.address()[1], peer.address()[2], peer.address()[3], peer.address()[4], peer.address()[5]);

    for (size_t ii = 0; ii < len; ii++) {
        Serial.write(data[ii]);
    }
}

void bluetooth_interface_thread(void *params){
    for(;;){
        
        delay(3000);
    }
}

void bluetooth_interface_init(void){
    BLE.on();
    BLE.addCharacteristic(txCharacteristic);
    BLE.addCharacteristic(rxCharacteristic);
    BLE.addCharacteristic(batteryLevelCharacteristic);

    BleAdvertisingData data;
    data.appendServiceUUID(serviceUuid);
    data.appendServiceUUID(batteryLevelService);
    BLE.advertise(&data);

    battery_ble_update_timer.start();
}