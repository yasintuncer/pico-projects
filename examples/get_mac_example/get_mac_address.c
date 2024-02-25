#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "cyw43.h"


void get_mac_adderss(uint8_t *mac)
{
    cyw43_arch_init();
    cyw43_arch_enable_sta_mode();
    cyw43_wifi_get_mac(&cyw43_state, CYW43_ITF_STA, mac);
}




int main()
{

    stdio_init_all();

    uint8_t mac[6];
    get_mac_adderss(mac);
    
    while (true)
    {
        printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        sleep_ms(1000);
    }

    return 0;
}
