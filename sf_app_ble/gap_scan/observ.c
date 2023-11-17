/*
 * observ.c
 *
 *  Created on: 20 jun 2023
 *      Author: temporal
 */

#include "observ.h"
#include "wiced_result.h"
#include <string.h>
#define maax_size 5

uint8_t 	dataFilt[10];   //5  usados en el nombre
uint8_t 	dataFiltm[6];   //6   usados en el nombre
uint8_t 	length3,length4;        //   usado en el UID
uint8_t *   p_data,* p_data4;
//unsigned char data_ma_save2[93];
char nombre[5][13], UID[5][11], URL[5][13],flag_name[5],flag_uid[5],flag_url[5];

/*Funcion usada en el scanner de Bluetooth*/
static void Observer_scan_result_cback( wiced_bt_ble_scan_results_t *p_scan_result, uint8_t *p_adv_data );
void actualizar_valores(char texto[], char data2[],int numnombre, int postext);
void actualizar_valores_url(char texto[], char data2[],int numnombre, int postext);
void actualizar_valores_uid(char texto[], char data2[],int numnombre, int postext);

void stop_scanner(void){
	wiced_bt_ble_observe (0,0, Observer_scan_result_cback);
}

void start_call_back_scanner(int savetime){
	WICED_BT_TRACE("\n init scaner \n");
	wiced_bt_ble_observe (1,savetime, Observer_scan_result_cback);

}

void timer_init_scann(char data2[],char data3[])
{
	uint8_t inicio_name=0, inicio_url=86, inicio_uid=156;
	for(int i=0;i<5;i++)
	{
		//WICED_BT_TRACE("\n Entro a verificar los valores \n");
		if(data2[inicio_name]=='t')
			{
				memset(nombre[i],'\0',13);
				memcpy(nombre[i],&data2[inicio_name+1],strlen(&data2[inicio_name+1]));
				WICED_BT_TRACE("\n nombre %s\n",&nombre[i]);
			}
		if(data2[inicio_url]=='t')
			{
				memset(URL[i],'\0',13);
				memcpy(URL[i],&data2[inicio_url+1],strlen(&data2[inicio_url+1]));
				WICED_BT_TRACE("\n url %s\n",&URL[i]);
			}
		if(data2[inicio_uid]=='t')
			{
				memset(UID[i],'\0',11);
				memcpy(UID[i],&data2[inicio_uid+1],strlen(&data2[inicio_uid+1]));
				WICED_BT_TRACE("\n url %s\n",&UID[i]);
			}

		inicio_name = inicio_name + 14;
		inicio_url = inicio_url +14;
		inicio_uid = inicio_uid + 14;
	}

	if(data2[85] == 't')
			{
				WICED_BT_TRACE("\n se dejo encedido el scanner\n");
				//Guardo el valor de el tiempo a escanear
				int time[4];
				for(int m=0;m<4;m++)
				{
					time[m]=data3[m]-'0';
				}
				int m=0, savetime=0;
				while(m<4 && time[m]!=-48)
				{
					if(m==0)savetime=time[m];
					else
					{
						savetime=savetime*10;
						savetime=savetime+time[m];
					}
					m++;
				}
				wiced_bt_ble_observe (1,savetime, Observer_scan_result_cback);
			}
}

void choos_what_scaner(char texto[], char data2[], char data3[])
{
	if(memcmp("name",&texto[12],4)==0)
		{
		  	  	  	  	  	  	  	  	  	  	  	  			/* nombre[30]    Val EEPROM   0,1,2,3,4,5  posicion inicial*/
		if(memcmp("1",&texto[17],1)==0)actualizar_valores		(    texto    ,    data2   ,   0        ,      1         );
		else if(memcmp("2",&texto[17],1)==0)actualizar_valores	(	 texto    ,    data2   ,   1        ,      15        );
		else if(memcmp("3",&texto[17],1)==0)actualizar_valores	(	 texto    ,    data2   ,   2        ,      29        );
		else if(memcmp("4",&texto[17],1)==0)actualizar_valores	(	 texto    ,    data2   ,   3        ,      43        );
		else if(memcmp("5",&texto[17],1)==0)actualizar_valores	(	 texto    ,    data2   ,   4        ,      57        );
		}
	else if(memcmp("url",&texto[12],3)==0)
		{
			if(memcmp("1",&texto[16],1)==0)actualizar_valores_url		(    texto    ,    data2   ,   0     ,      87       );
			else if(memcmp("2",&texto[16],1)==0)actualizar_valores_url	(    texto    ,    data2   ,   1     ,      101      );
			else if(memcmp("3",&texto[16],1)==0)actualizar_valores_url	(    texto    ,    data2   ,   2     ,      115      );
			else if(memcmp("4",&texto[16],1)==0)actualizar_valores_url	(    texto    ,    data2   ,   3     ,      129      );
			else if(memcmp("5",&texto[16],1)==0)actualizar_valores_url	(    texto    ,    data2   ,   4     ,      143      );
		}
	else if(memcmp("uid",&texto[12],3)==0)
			{
				if(memcmp("1",&texto[16],1)==0)actualizar_valores_uid		(    texto    ,    data2   ,   0     ,      157       );
				else if(memcmp("2",&texto[16],1)==0)actualizar_valores_uid	(    texto    ,    data2   ,   1     ,      171       );
				else if(memcmp("3",&texto[16],1)==0)actualizar_valores_uid	(    texto    ,    data2   ,   2     ,      185       );
				else if(memcmp("4",&texto[16],1)==0)actualizar_valores_uid	(    texto    ,    data2   ,   2     ,      199       );
				else if(memcmp("5",&texto[16],1)==0)actualizar_valores_uid	(    texto    ,    data2   ,   2     ,      213       );
			}
	else if(memcmp("on",&texto[12],2)==0)
		{
			int time[4];
			WICED_BT_TRACE("\n ***START SCANNER*** \n");
			//en el 98 se deja la t para decir que se ensendio el scanner
			data2[85]='t';
			//WICED_BT_TRACE("\n bandera en lugar 85 %c \n",data2[85]);

			//Guardo el valor de el tiempo a escanear
			for(int m=0;m<4;m++)
		    {
		      time[m]=texto[m+15]-'0';
		    }
			int m=0, savetime=0;
			while(m<4 && time[m]!=-48)
			{
				if(m==0)savetime=time[m];
				else
				{
					savetime=savetime*10;
					savetime=savetime+time[m];
			    }
			   m++;
			}
			start_call_back_scanner(savetime);
			memcpy(&data3[0],&texto[15],strlen(&texto[15]));
		}
	if(memcmp("off",&texto[12],3)==0)
					{
						//en el 98 se deja la f para decir que se apago el scanner
						data2[85]='f';
						//flag_name[numnombre]=data2[0];
						stop_scanner();
						WICED_BT_TRACE("\n ***STOP SCANER*** \n");
					}
}

void actualizar_valores(char texto[], char data2[], int numnombre, int postext)
{
		if(strlen(&texto[19])<13)
		{
			/*******Limpio data2[90], limpio tambien nombre[][]******/
			memset(&data2[postext],'\0',12);
			memset(nombre[numnombre],'\0',12);
			/*******Copio los valores en data2 y en nombre[][]*******/
			memcpy(&data2[postext],&texto[19],strlen(&texto[19]));
			memcpy(nombre[numnombre],&data2[postext],strlen(&data2[postext]));
			/*******Imprimo la informacion guardada******/
			WICED_BT_TRACE("\n ****************************");
			WICED_BT_TRACE("\n data_ma_save %s", &data2[postext]);
			WICED_BT_TRACE("\n nombre %s [%d]",nombre[numnombre],numnombre + 1);
			WICED_BT_TRACE("\n The name to search was configurate !!!!");
			WICED_BT_TRACE("\n **************************** \n");

			wiced_hal_gpio_configure_pin(reception_led, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW);
			init_timer();

			/*******Asigno la bandera al inicio de cada nombre, indicando que esta activo*******/
			data2[postext-1]='t';
			flag_name[numnombre]=data2[1-postext];
			//WICED_BT_TRACE("\n flag save in data2, falg name %c %c\n",data2[1-postext],flag_name[numnombre]);
		}
		else WICED_BT_TRACE("\n The name entered is greater than the allowed, enter it again...\n");

}

void actualizar_valores_url(char texto[], char data2[], int numnombre, int postext)
{
		if(strlen(&texto[18])<13)     //En el lugar 18 se encuentra el URL ha poner
		{
			/*******Limpio data2[90], limpio tambien nombre[][]******/
			memset(&data2[postext],'\0',12);
			memset(URL[numnombre],'\0',12);
			/*******Copeo los valores en data2 y en nombre[][]*******/
			memcpy(&data2[postext],&texto[18],strlen(&texto[18]));
			memcpy(URL[numnombre],&data2[postext],strlen(&texto[18]));
			/*******Imprimo la informacion guardada******/
			WICED_BT_TRACE("\n data_ma_save %s", &data2[postext]);
			WICED_BT_TRACE("\n URL %s [%d] \n",&URL[numnombre],numnombre + 1);
			WICED_BT_TRACE("\n The URL to search was configurate !!!! \n");
			wiced_hal_gpio_configure_pin(reception_led, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW);
			init_timer();
			/*******Asigno la bandera al inicio de cada nombre, indicando que esta activo*******/
			data2[postext-1]='t';
			flag_url[numnombre]=data2[1-postext];
			//WICED_BT_TRACE("\n flag save in data2, falg url %c %c\n",data2[1-postext],flag_url[numnombre]);
		}
		else WICED_BT_TRACE("\n The url entered is greater than the allowed, enter it again...\n");
}

void actualizar_valores_uid(char texto[], char data2[], int numnombre, int postext)
{
		if(strlen(&texto[18])<11)     //En el lugar 18 se encuentra el URL ha poner
		{
			/*******Limpio data2[90], limpio tambien nombre[][]******/
			memset(&data2[postext],'\0',10);
			memset(UID[numnombre],'\0',10);
			/*******Copeo los valores en data2 y en nombre[][]*******/
			for(int i=18;i<28;i++)
				{
					if(texto[i]-'0'<10)data2[postext+i-18]=texto[i]-'0';
					else data2[postext+i-18]=texto[i];
				}
			//memcpy(&data2[postext],&texto[18],strlen(&texto[18]));
			memcpy(UID[numnombre],&data2[postext],strlen(&data2[postext]));
			/*******Imprimo la informacion guardada******/
			WICED_BT_TRACE("\n data_ma_save %s", &data2[postext]);
			WICED_BT_TRACE("\n UID %s [%d] \n",&UID[numnombre],numnombre + 1);
			WICED_BT_TRACE("\n The UID to search was configurate !!!! \n");
			/*******Asigno la bandera al inicio de cada nombre, indicando que esta activo*******/
			data2[postext-1]='t';
			flag_uid[numnombre]=data2[1-postext];
			//WICED_BT_TRACE("\n flag save in data2, falg uid %c %c\n",data2[1-postext],flag_url[numnombre]);
		}
		else WICED_BT_TRACE("\n The uid entered is greater than the allowed, enter it again...\n");
}

void Observer_scan_result_cback( wiced_bt_ble_scan_results_t *p_scan_result, uint8_t *p_adv_data )
{
		    wiced_bt_device_address_t static_addr;    //arreglo de 6 unidades static_addr[6]
		    wiced_bt_dev_read_local_addr(static_addr );  //Read the local device address, means read the own device address

		    //Usado para el nombre, 		 URL              uid
		    uint8_t * p_name1=NULL,    * p_name2=NULL,    * p_name3=NULL;
		    uint8_t 	length3=0, 			length4=0,		  length5=0;

		    /* Value for rssi */
		    int8_t value_rssi;

//		    p_name3=&p_adv_data[5];
//		    WICED_BT_TRACE("DATA: ");
//            wiced_hal_puart_print(p_name3);
//            WICED_BT_TRACE("\n");
		    /* Con p_sacn_reslt le lo que haya llegado, dar clic en para ver estructura wiced_bt_ble_scan_results_t*/
		    if( p_scan_result)
		    	{
		    	value_rssi= p_scan_result->rssi;

		    	/****************** Serch name *********************/
		    	p_name1 = wiced_bt_ble_check_advertising_data( p_adv_data, BTM_BLE_ADVERT_TYPE_NAME_COMPLETE, &length3 );  //BTM_BLE_ADVERT_TYPE_128SRV_COMPLETE
		    	if(p_name1 != NULL)
		    	{
		    		for (int xn=0;xn<=maax_size;xn++)
		    		{
		    			if (strlen(nombre[xn])!=0)
		    			{
		    				//Busco lamparas
		    				memcpy(scanner_name,p_name1,5);
		    				//WICED_BT_TRACE("\n ->%s ->%s\n",scanner_name,nombre[xn]);
		    				//WICED_BT_TRACE("\n %d %d ",strlen(nombre[xn]),strlen(scanner_name));

		    				if(memcmp(scanner_name , nombre[xn],5)==0)
		    				//if(strstr(p_name1 , nombre[xn]))
		    				{
		    					if(memcmp(scanner_name ,"L4SEC",5)==0 && p_scan_result->remote_bd_addr[0] !=0 &&
		    							p_scan_result->remote_bd_addr[1] !=0 && p_scan_result->remote_bd_addr[2] !=0 &&
										p_scan_result->remote_bd_addr[3] !=0 )
		    					WICED_BT_TRACE("MAC: %02X:%02X:%02X:%02X:%02X:%02X %d BSL\n", p_scan_result->remote_bd_addr[0],p_scan_result->remote_bd_addr[1],p_scan_result->remote_bd_addr[2],p_scan_result->remote_bd_addr[3],p_scan_result->remote_bd_addr[4],p_scan_result->remote_bd_addr[5],value_rssi);
		    					if(memcmp(scanner_name ,"LAIRD",5)==0)
		    					WICED_BT_TRACE("MAC: %02X:%02X:%02X:%02X:%02X:%02X %d BSL\n", p_scan_result->remote_bd_addr[0],p_scan_result->remote_bd_addr[1],p_scan_result->remote_bd_addr[2],p_scan_result->remote_bd_addr[3],p_scan_result->remote_bd_addr[4],p_scan_result->remote_bd_addr[5],value_rssi);
		    				}
		    				memset(scanner_name,'\0',5);
		    			}
		    		}
		    	}
		    	/**************      Serch URL***************/
		    			    			p_name2 = wiced_bt_ble_check_advertising_data( p_adv_data, BTM_BLE_ADVERT_TYPE_SERVICE_DATA, &length4 );  //BTM_BLE_ADVERT_TYPE_128SRV_COMPLETE
		    			    			if(p_name2 != NULL)
		    			    				{
		    			    				//WICED_BT_TRACE("\n ---->%s: %B ---->%s \n",&p_name2[5],p_scan_result->remote_bd_addr, URL[0]); ----->
		    			    					if((strlen(URL[0])!=0 && memcmp(URL[0],&p_name2[5],strlen(URL[0]))==0)||
		    			    					   (strlen(URL[1])!=0 && memcmp(URL[1],&p_name2[5],strlen(URL[1]))==0)||
												   (strlen(URL[2])!=0 && memcmp(URL[2],&p_name2[5],strlen(URL[2]))==0)||
												   (strlen(URL[3])!=0 && memcmp(URL[3],&p_name2[5],strlen(URL[3]))==0)||
												   (strlen(URL[4])!=0 && memcmp(URL[4],&p_name2[5],strlen(URL[4]))==0))
		    			    						{
		    			    							//WICED_BT_TRACE_ARRAY(&p_name2[5],strlen(&p_name2[5]),"Found URL	");
		    			    							//WICED_BT_TRACE("FOUND Matching Device with BD Address: [%B] \n", p_scan_result->remote_bd_addr);
		    			    							//WICED_BT_TRACE("\n");
		    			    						WICED_BT_TRACE("MAC: %02X:%02X:%02X:%02X:%02X:%02X %d BEA\n", p_scan_result->remote_bd_addr[0],p_scan_result->remote_bd_addr[1],p_scan_result->remote_bd_addr[2],p_scan_result->remote_bd_addr[3],p_scan_result->remote_bd_addr[4],p_scan_result->remote_bd_addr[5],value_rssi);
		    			    						}
		    			    					/*UID*/
		    			    					if( (strlen(UID[0])!=0 && memcmp(UID[0],&p_name2[4],10)==0)||
		    			    						(strlen(UID[1])!=0 && memcmp(UID[1],&p_name2[4],10)==0)||
													(strlen(UID[2])!=0 && memcmp(UID[2],&p_name2[4],10)==0)||
													(strlen(UID[3])!=0 && memcmp(UID[3],&p_name2[4],10)==0)||
													(strlen(UID[4])!=0 && memcmp(UID[4],&p_name2[4],10)==0))
		    			    					{
		    			    						WICED_BT_TRACE_ARRAY(&p_name2[5],strlen(&p_name2[5]),"Found UID	");
		    			    						WICED_BT_TRACE("FOUND Matching Device with BD Address: [%B] \n", p_scan_result->remote_bd_addr);
		    			    						WICED_BT_TRACE("\n");
		    			    					}
		    			    				}
		    	}
}

