/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <string.h>
#include <stdlib.h>
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* PA0 脉冲输出（中断驱动）状态变量（使用硬件 PWM：表示剩余周期数） */
volatile uint32_t g_pa0_remaining_edges = 0; /* 剩余周期数 */
volatile uint8_t  g_pa0_active = 0;         /* 是否正在输出 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void ProcessUSBFrame(uint8_t *buf, uint16_t len);
static void StartPA0PulseTrain(uint32_t freq, uint32_t count);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/*
 * 解析 USB 串口接收到的帧，格式示例: A500B10C
 * A 为帧头，B 为分隔符，C 为帧尾
 * A 与 B 之间为频率（Hz），B 与 C 之间为方波个数
 */
void ProcessUSBFrame(uint8_t *buf, uint16_t len)
{
  if (buf == NULL || len == 0) return;
  uint8_t *p = buf;
  uint8_t *end = buf + len;
  uint8_t *startA = NULL, *sepB = NULL, *tailC = NULL;

  for (; p < end; p++) {
    if (*p == 'A') { startA = p; break; }
  }
  if (startA == NULL) return;
  for (p = startA + 1; p < end; p++) {
    if (*p == 'B') { sepB = p; break; }
  }
  if (sepB == NULL) return;
  for (p = sepB + 1; p < end; p++) {
    if (*p == 'C') { tailC = p; break; }
  }
  if (tailC == NULL) return;

  int freq = 0;
  int count = 0;
  size_t lenFreq = sepB - (startA + 1);
  size_t lenCount = tailC - (sepB + 1);
  if (lenFreq > 0 && lenFreq < 16) {
    char tmp[16]; memset(tmp, 0, sizeof(tmp));
    memcpy(tmp, startA + 1, lenFreq);
    freq = atoi(tmp);
  }
  if (lenCount > 0 && lenCount < 16) {
    char tmp2[16]; memset(tmp2, 0, sizeof(tmp2));
    memcpy(tmp2, sepB + 1, lenCount);
    count = atoi(tmp2);
  }

  if (freq > 0 && count > 0) {
    /* 向主机应答 OK */
    CDC_Transmit_FS((uint8_t *)"OK\r\n", 4);
    StartPA0PulseTrain((uint32_t)freq, (uint32_t)count);
  }
}

/*
 * 简单实现：使用 HAL_Delay（ms）在 PA0 上输出方波。
 * 说明：该实现为阻塞方式，分辨率为毫秒；频率很高或精确控制
 * 需求时建议改为硬件定时器（PWM 或定时器中断）实现。
 */
static void StartPA0PulseTrain(uint32_t freq, uint32_t count)
{
  /* 使用 TIM2 中断驱动非阻塞方波输出（用户在 CubeMX 中已将 TIM2 配置为 100ms 周期中断）。
     算法：将每个方波的半周期对应为若干 TIM2 中断间隔（向上取整），在 HAL_TIM_PeriodElapsedCallback 中按计数切换 PA0。
  */
  if (freq == 0 || count == 0) return;

  /* 采用硬件 PWM：设置 TIM2 的 ARR/CCR 以得到目标频率并以 50% 占空比输出，使用更新中断计数周期数后停止 PWM。 */
  /* 计算定时器计数时钟：从 PCLK1 获取并考虑 APB1 prescaler（TIMx 在 APB1 上时，当 APB1 prescaler != 1，定时器时钟 = PCLK1*2） */
  uint32_t pclk1 = HAL_RCC_GetPCLK1Freq();
  uint32_t timer_clk = pclk1;
#if defined(RCC_CFGR_PPRE1_DIV1)
  /* 如果宏可用，尝试更精确判断（兼容性保护） */
  if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1) {
    timer_clk = pclk1 * 2U;
  }
#else
  /* 退回到常见的 STM32F1 行为：APB1 prescaler != 1 时定时器时钟翻倍 */
  if ((RCC->CFGR & (RCC_CFGR_PPRE1)) != 0) {
    timer_clk = pclk1 * 2U;
  }
#endif

  uint32_t prescaler = htim2.Init.Prescaler + 1U;
  uint64_t counter_clk = (uint64_t)timer_clk / prescaler; /* 计数器时钟（Hz） */
  if (counter_clk == 0) counter_clk = 1;

  /* 使用 64 位精确计算 ARR = round(counter_clk / freq) - 1 */
  uint64_t arr64 = (counter_clk + (freq / 2)) / freq;
  if (arr64 == 0) arr64 = 1;
  if (arr64 > 0xFFFFFFFFULL) arr64 = 0xFFFFFFFFULL;
  uint32_t arr = (uint32_t)(arr64 - 1ULL);
  uint32_t ccr = (uint32_t)((arr64) / 2ULL); /* 50% 占空比 */

  __disable_irq();
  g_pa0_remaining_edges = count; /* 每个周期计数一次 */
  g_pa0_active = 1;
  /* 设置 ARR 和 CCR */
  __HAL_TIM_SET_AUTORELOAD(&htim2, arr);
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ccr);
  __enable_irq();

  /* 调试打印：timer_clk / ARR / CCR */
  char dbgbuf[80];
  int n = snprintf(dbgbuf, sizeof(dbgbuf), "TCLK=%llu ARR=%lu CCR=%lu\r\n", (unsigned long long)counter_clk, (unsigned long)arr, (unsigned long)ccr);
  if (n > 0) {
    CDC_Transmit_FS((uint8_t*)dbgbuf, (uint16_t)n);
  }

  /* 启动 TIM2 基础计数中断和 PWM 输出 */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

/* TIM2 中断回调：在 USER CODE 区实现中断驱动的 PA0 切换 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == NULL) return;
  if (htim->Instance == TIM2) {
    if (!g_pa0_active) return;
    if (g_pa0_remaining_edges > 0) {
      g_pa0_remaining_edges--;
    }
    if (g_pa0_remaining_edges == 0) {
      /* 停止 PWM，确保输出为低 */
      HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
      g_pa0_active = 0;
      HAL_TIM_Base_Stop_IT(&htim2);
    }
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
