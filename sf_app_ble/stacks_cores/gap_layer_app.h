/*
 * gap_layer_app.h
 *
 *  Created on: 1 mar 2021
 *      Author: Jared
 */

#ifndef SF_APP_BLE_STACKS_CORES_GAP_LAYER_APP_H_
#define SF_APP_BLE_STACKS_CORES_GAP_LAYER_APP_H_

/************************************************/
wiced_result_t  status111,status22,status33, status_mac;

uint16_t        numbytes_mac;
unsigned char data_ma_save2[93]; //57 a 93 para nombre y URL y UID
unsigned char data2[230]; // Se usara solo para guardar nomres
unsigned char data3[10];

#define Change_IP "CIP"
#define Change_MASCARA "CMA"
#define Change_GATEWAY "CGA"
#define Cchange_DNS1 "CD1"
#define Cchange_DNS2 "CD2"

/*
 * 							Variables globales usadas en el UART para saber el estado de UUID
 */
char texto_global[50];

typedef struct
{
	uint8_t value_d;
	uint8_t value_u;
	uint8_t value_dt;
	uint8_t value_ut;
	uint8_t value_n;

}data_config_t;

data_config_t data_select[6];

#define BEACON_EDDYSTONE_TLM 4



/* User defined UUID for iBeacon */
#define UUID_IBEACON     0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f

char datafv_cfb[8]={0x4c,0x41,0x49,0x52,0x44,0x53,0x4c,0x50};
char datafv_cfbV[8]={0x4c,0x41,0x49,0x52,0x44,0x53,0x54,0x56};
char datac_cfb[6];
char dataa_cfb2[14];

extern unsigned char data_rssi_save1[10];

extern const wiced_bt_cfg_settings_t app_cfg_settings2;
extern const wiced_bt_cfg_buf_pool_t app_buf_pools2[];

void gap_stack_init(void);
void gap_transferA(void);
void gap_transferB(void);

static void                     beacon_init(void);
static wiced_result_t           beacon_management_callback(wiced_bt_management_evt_t event, wiced_bt_management_evt_data_t *p_event_data);
static void                     beacon_advertisement_stopped(void);
static void                     beacon_set_app_advertisement_data2();
void                            beacon_set_app_advertisement_data3(void);
void                            gap_transferER(void);
void                            set_data_base(void);

extern void	                    config_Transceiver(void);
extern void                     init_config_logs(void);
extern void                     init_mac_logs(void);
extern void                     start_observe(void);

extern void                     set_outPuts(void);
extern void                     set_intPuts(void);
extern void                     register_pin_interrupt(void);
extern void                     event_select_OTA(void);
extern void                     set_adc_p(void);
extern void                     event_select_SPP(void);
extern void                     set_rssi(void);

extern void                     config_clk_timers(void);
extern void                     start_BTimers2(void);

extern void process_SOM(uint8_t *data_S_OM);
extern void process_change(uint8_t *data_S_OM,uint16_t data_len);   //Mio para mandar los datos enviados por la aplicación
extern void 					init_timer(void);      //Timer para blinkear led 26 cuando se mandan datos

extern void start_call_back_scanner(int time);

#endif /* SF_APP_BLE_STACKS_CORES_GAP_LAYER_APP_H_ */
