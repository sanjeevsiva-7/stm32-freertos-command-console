/*
 * led_effect.c
 *
 *  Created on: 24-Oct-2026
 *      Author: LENOVO
 */


#include "main.h"


void led_effect_stop(void){
	for(int i = 0; i < 4; i++){
		xTimerStop(handle_led_timer[i],portMAX_DELAY);
	}
}

void led_effect(int n){
	led_effect_stop();//it stop the currently running led effect
	xTimerStart(handle_led_timer[n - 1],portMAX_DELAY);
}

void turn_off_all_led(void) {
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4 , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

}

void turn_on_all_led(void){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4 , GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
}


void LED_effect1(void){
	static int flag = 1;
	(flag ^= 1) ? (turn_off_all_led()) : (turn_on_all_led());
}


void turn_on_even_led(void) {
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4 , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

}

void turn_on_odd_led(void){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4 , GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}

void LED_effect2(void){
	static int flag = 1;
	(flag ^= 1) ? (turn_on_even_led()) : (turn_on_odd_led());
}

void led_control(int value){
	static const uint16_t led_pins[4] = { GPIO_PIN_4, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8 };
	for(int k = 0; k < 4 ;k++){
		HAL_GPIO_WritePin(GPIOA,led_pins[k] , ((value >> k) & 0x1 )? GPIO_PIN_SET : GPIO_PIN_RESET );
	}

}


void LED_effect3(void){
	static int i = 0;
	led_control(0x1 << (i++ % 4));

}

void LED_effect4(void){
	static int i = 0;
	led_control(0x8 >> (i++ % 4));

}
