/*
 * as608.h
 *
 *  Created on: 2018年4月25日
 *      Author: weihaochen
 */

#ifndef INC_AS608_H_
#define INC_AS608_H_


#include "DSP2833x_Device.h"


#define             CHAR_BUFFER_1         (0x01)
#define             CHAR_BUFFER_2         (0x02)
#define             TOUCH                 (0)
#define             UNTOUCH               (1)

typedef struct {

    u16 pageID;//指纹ID
    u16 mathscore;//匹配得分

}   SEARCH_RESULT;

typedef struct {

    u16 PS_max;//指纹最大容量
    u8  PS_level;//安全等级
    u32 PS_addr;
    u8  PS_size;//通讯数据包大小
    u8  PS_N;//波特率基数N

} SYS_PARA;

typedef struct  as608_t {

    struct as608_t  *self;
    uint32          device_address;
    uint8    callback_str[50];
    SEARCH_RESULT   search_result;
    SYS_PARA        system_para;
    bool    read_flag;
    uint16  recv_count;

    void    (*init)( struct as608_t *this);
    uint8    (*reset)( struct as608_t *this );
    uint8    (*pin_set) ( struct as608_t *this );

    uint8    (*read_state)  ( struct as608_t *this );
    uint8    (*get_image) ( struct as608_t *this );
    uint8    (*gen_char) ( struct as608_t *this , uint8  buffer_id);
    uint8    (*match) ( struct as608_t *this );
    uint8    (*search) ( struct as608_t *this ,uint8 buffer_id, uint16 start_page, uint16 page_num, SEARCH_RESULT *p);
    uint8    (*reg_model) ( struct as608_t *this );
    uint8    (*store_char) ( struct as608_t *this, uint8 buffer_id, uint16 page_id );
    uint8    (*dele_char) ( struct as608_t *this, uint8 page_id, uint16 n );
    uint8    (*empty) ( struct as608_t *this );
    uint8    (*write_reg) ( struct as608_t *this , uint8 reg_num, uint8 data);
    uint8    (*read_sys_para) ( struct as608_t *this, SYS_PARA *p );
    uint8    (*set_addr) ( struct as608_t *this , uint32 addr);
    uint8    (*valid_templete_num) ( struct as608_t *this , uint16 *valid_n );
    uint8    (*hand_shake) ( struct as608_t *this, uint32 addr );
    uint8*  (*ensure_message) ( struct as608_t *this ,uint8 ensure);
    uint8*  (*judge_str) ( struct as608_t *this, uint16 waittime );
    uint8   (*high_speed_search)( struct as608_t * this, uint8 id,
            u16 start_page, u16 page_num,
            SEARCH_RESULT *p  );
    void    (*add_finger)( struct as608_t * this );
    void    (*press_finger)( struct as608_t *this );
    void    (*send_byte)( BYTE byte );
    void    (*send_head)( void );
    void    (*send_addr)( uint32 addr );
    void    (*send_flag)( uint8 flag );
    void    (*send_length)( uint16 length );
    void    (*send_cmd)( uint8 cmd );
    void    (*send_check)( uint16 check );
    bool    (*uart_process)( struct as608_t *this, BYTE val );


} AS608;

extern void AS608_INIT( AS608 *self );

void    as608_init( struct as608_t *this);
uint8    as608_reset( struct as608_t *this );
uint8    as608_pin_set( struct as608_t *this );
uint8    as608_read_state( struct as608_t *this );
uint8    as608_get_image( struct as608_t *this );
uint8    as608_gen_char( struct as608_t *this , uint8  buffer_id);
uint8    as608_match( struct as608_t *this );
uint8    as608_search( struct as608_t *this ,uint8 buffer_id, uint16 start_page, uint16 page_num, SEARCH_RESULT *p);
uint8    as608_reg_model( struct as608_t *this );
uint8    as608_store_char( struct as608_t *this, uint8 buffer_id, uint16 page_id );
uint8    as608_dele_char( struct as608_t *this, uint8 page_id, uint16 n );
uint8    as608_empty( struct as608_t *this );
uint8    as608_write_reg( struct as608_t *this , uint8 reg_num, uint8 data);
uint8    as608_read_sys_para( struct as608_t *this, SYS_PARA *p );
uint8    as608_set_addr( struct as608_t *this , uint32 addr);
uint8    as608_valid_templete_num( struct as608_t *this , uint16 *valid_n );
uint8    as608_hand_shake( struct as608_t *this, uint32 addr );
void    as608_send_byte ( BYTE byte );
void    as608_send_head( void );
void    as608_send_addr( uint32 addr );
void    as608_send_flag( uint8 flag );
void    as608_send_length( uint16 length );
void    as608_send_cmd( uint8 cmd );
void    as608_send_check( uint16 check );
static  uint8*   as608_judge_str( struct as608_t *this, uint16 wait_time );
uint8*    as608_ensure_message( struct as608_t *this ,uint8 ensure);
bool    as608_uart_process( struct as608_t *this, BYTE val );
uint8    as608_high_speed_search( AS608* this, uint8 id,
                                 u16 start_page, u16 page_num,
                                 SEARCH_RESULT *p  );

void    as608_add_finger( AS608* this );
void    as608_press_finger( AS608 *this );
#endif /* INC_AS608_H_ */
