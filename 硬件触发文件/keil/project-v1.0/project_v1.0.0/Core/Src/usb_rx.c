#include "usb_rx.h"
#include "main.h"
#include "gpio.h"
#include "usbd_cdc.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

void USB_RX_Process(void)
{
  if (hUsbDeviceFS.pClassData == NULL) return;
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
  if (hcdc == NULL) return;
  uint32_t len = hcdc->RxLength;
  if (len == 0) return;
  uint8_t *buf = hcdc->RxBuffer;
  /* prepare bit-band pointer to PA0 (GPIOA ODR bit 0) for minimal-latency writes */
  uint32_t gpio_odr_addr = (uint32_t)&GPIOA->ODR;
  #define PERIPH_BB_BASE  ((uint32_t)0x42000000UL)
  #define PERIPH_BASE     ((uint32_t)0x40000000UL)
  #define BITBAND_PERI_ADDR(addr, bit) (PERIPH_BB_BASE + (((uint32_t)(addr) - PERIPH_BASE) << 5) + ((bit) << 2))
  volatile uint32_t *pa0_bb = (volatile uint32_t *)BITBAND_PERI_ADDR(gpio_odr_addr, 0);

  for (uint32_t i = 0; i < len; i++) {
    uint8_t b = buf[i];
    if (b == 'H') {
      *pa0_bb = 1U; /* set bit */
    } else if (b == 'L') {
      *pa0_bb = 0U; /* clear bit */
    }
  }
  /* undef macros to avoid leaking into other files */
  #undef PERIPH_BB_BASE
  #undef PERIPH_BASE
  #undef BITBAND_PERI_ADDR
  /* Mark as consumed */
  hcdc->RxLength = 0;
}
