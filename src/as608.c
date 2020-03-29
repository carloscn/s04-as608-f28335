/*
 * as608.c
 *
 *  Created on: 2018年4月25日
 *      Author: weihaochen
 */
#include "global.h"


void AS608_INIT( AS608 *this ) {

    this->init = &as608_init;
    this->reset = &as608_reset;
    this->pin_set = &as608_pin_set;
    this->read_state = as608_read_state;
    this->get_image = &as608_get_image;
    this->gen_char =  &as608_gen_char;
    this->match =  &as608_match;
    this->search =  &as608_search;
    this->reg_model =  &as608_reg_model;
    this->store_char =  &as608_store_char;
    this->dele_char =  &as608_dele_char;
    this->empty =  &as608_empty;
    this->write_reg =  &as608_write_reg;
    this->read_sys_para =  &as608_read_sys_para;
    this->set_addr =  &as608_set_addr;
    this->valid_templete_num =  &as608_valid_templete_num;
    this->hand_shake = &as608_hand_shake;
    this->ensure_message =  &as608_ensure_message;
    this->send_byte =  &as608_send_byte;
    this->send_head =  &as608_send_head;
    this->send_addr = &as608_send_addr;
    this->send_flag =  &as608_send_flag;
    this->send_length =  &as608_send_length;
    this->send_cmd =  &as608_send_cmd;
    this->send_check =  &as608_send_check;
    this->judge_str = &as608_judge_str;
    this->high_speed_search =   &as608_high_speed_search;
    this->add_finger    =   &as608_add_finger;
    this->press_finger   =   &as608_press_finger;

    this->read_flag =   false;

    this->init( this );
}

void    as608_send_byte ( BYTE byte ) {

    byte = byte & 0xFF;
    scib_xmit(byte);

}

void    as608_init( AS608 *this) {

    this->device_address    =   0xFFFFFFFF;


}
uint8    as608_reset( AS608 *this ) {

}
uint8    as608_pin_set( AS608 *this ) {

    EALLOW;
    //GpioMuxRegs.GPBMUX.bit.PWM8_GPIOB1  =   0;
    //GpioMuxRegs.GPBDIR.bit.GPIOB1       =   0;
    EDIS;

}
uint8    as608_read_state( AS608 *this ) {
    uint16 i = 0;
    uint16 count = 0;
    for ( i = 0; i < 1000; i ++ ) {
        if ( GpioDataRegs.GPADAT.bit.GPIO13 == 0 ) {
            count ++;
        }
        DELAY_US(10);
    }
    if ( count > 800 ) {
        return TRUE;
    }else {
        return FALSE;
    }
}
uint8    as608_get_image( AS608 *this ) {

    uint16  check_byte;
    uint8   ensure;
    u8      *data;

    this->send_head();
    this->send_addr( this->device_address );
    this->send_flag(0x01);
    this->send_length( 0x03 );
    this->send_cmd( 0x01 );
    check_byte    = 0x01 + 0x03 + 0x01;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );
    if( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    this->ensure_message(this, ensure);
    return ensure;
}
uint8    as608_gen_char( AS608 *this , uint8  buffer_id) {

    uint16  check_byte;
    uint8   ensure;
    u8      *data;

    this->send_head();
    this->send_addr( this->device_address );
    this->send_flag(0x01);
    this->send_length( 0x04 );
    this->send_cmd( 0x02 );
    this->send_byte( buffer_id );
    check_byte    = 0x01 + 0x04 + 0x02 + buffer_id;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );
    if( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    this->ensure_message(this, ensure);
    return ensure;


}
uint8    as608_match( AS608 *this ) {

    uint16  check_byte;
    uint8   ensure;
    uint8   *data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x03 );
    this->send_cmd( 0x03 );
    check_byte  =   0x01 + 0x03 +0x03;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if ( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    this->ensure_message(this, ensure);
    return ensure;

}
uint8    as608_search( AS608 *this ,uint8 buffer_id, uint16 start_page, uint16 page_num, SEARCH_RESULT *p) {

    uint16  check_byte;
    uint8   ensure;
    uint8   *data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x08 );
    this->send_cmd( 0x04 );
    this->send_byte( buffer_id );
    this->send_byte( start_page >> 8 );
    this->send_byte( start_page );
    this->send_byte( page_num >> 8 );
    this->send_byte( page_num );
    check_byte  =   0x01 + 0x08 + 0x04 +buffer_id + ( start_page >> 8 ) + ( start_page ) + \
            ( page_num >> 8 ) + ( page_num );
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if ( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    this->ensure_message(this, ensure);
    return ensure;
}

uint8    as608_high_speed_search( AS608* this, uint8 id,
                                  u16 start_page, u16 page_num,
                                  SEARCH_RESULT *p  ) {
    uint16  check_sum;
    u8  ensure;
    u8  *data;

    this->send_head();
    this->send_addr( this->device_address );
    this->send_flag( 0x01 );
    this->send_length( 0x08 );
    this->send_cmd( 0x1b );
    this->send_byte( id );
    this->send_byte( start_page >> 8 );
    this->send_byte( start_page );
    this->send_byte( page_num >> 8 );
    this->send_byte( page_num );
    check_sum   =   0x01 + 0x08 + 0x1b + id + (start_page >> 8) + (start_page) + (page_num >> 8) + (page_num);
    this->send_check( check_sum );

    data = this->judge_str( this, 2000 );
    if( data ) {
        ensure  =   data[9];
        p->pageID       =   ( data[10] << 8 ) + data[11];
        p->mathscore    =   ( data[12] << 8 ) + data[13];
    }else {
        ensure = 0xFF;
    }

    return ensure;
}

uint8    as608_reg_model( AS608 *this ) {

    uint16  check_byte;
    uint8   ensure;
    uint8   *data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x03 );
    this->send_cmd( 0x05 );
    check_byte  =   0x01 + 0x03 + 0x05;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if ( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    this->ensure_message(this, ensure);
    return ensure;

}
uint8    as608_store_char( AS608 *this, uint8 buffer_id, uint16 page_id ) {

    uint16  check_byte;
    uint8   ensure;
    uint8   *data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x06 );
    this->send_cmd( 0x06 );
    this->send_byte( buffer_id );
    this->send_byte( page_id >> 8 );
    this->send_byte( page_id );

    check_byte  =   0x01 + 0x06 + 0x06 + buffer_id + (page_id >> 8) + (u8)(page_id);
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if ( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    this->ensure_message(this, ensure);
    return ensure;

}
uint8    as608_dele_char( AS608 *this, uint8 page_id, uint16 n ) {

    uint16  check_byte;
    uint8   ensure;
    uint8   *data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x07 );
    this->send_cmd( 0x0c );
    this->send_byte( page_id >> 8 );
    this->send_byte( page_id );
    this->send_byte( n >> 8 );
    this->send_byte( n );

    check_byte  =   0x01 + 0x07 + 0x0c + page_id >> 8 + (u8)page_id + n >> 8 + (u8)n;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if ( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    this->ensure_message(this, ensure);
    return ensure;

}
uint8    as608_empty( AS608 *this ) {

    uint16  check_byte;
    uint8   ensure;
    uint8   *data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x03 );
    this->send_cmd( 0x0D );
    check_byte  =   0x01 + 0x03 + 0x0D;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if ( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    this->ensure_message(this, ensure);
    return ensure;

}
uint8    as608_write_reg( AS608 *this , uint8 reg_num, uint8 val) {

    uint16  check_byte;
    uint8   ensure;
    uint8*  data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x05 );
    this->send_cmd( 0x0E );
    this->send_byte( reg_num );
    this->send_byte( val );

    check_byte  =   0x01 + 0x05 + 0x0E + reg_num + val;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if ( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    if ( ensure == 0 ) {
        //printf( "set para succussful.\n\r" );

    }else {
        // printf("\r\n%s",this->ensure_message(this, ensure) );
    }
    this->ensure_message(this, ensure);
    return ensure;

}
uint8    as608_read_sys_para( AS608 *this, SYS_PARA *p ) {

    uint16  check_byte;
    uint8   ensure;
    uint8   *data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x03 );
    this->send_cmd( 0x0F );
    check_byte  =   0x01 + 0x03 + 0x0F;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if ( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    if(data) {
        ensure = data[9];
        p->PS_max = (data[14]<<8)+data[15];
        p->PS_level = data[17];
        p->PS_addr=(data[18]<<24)+(data[19]<<16)+(data[20]<<8)+data[21];
        p->PS_size = data[23];
        p->PS_N = data[25];
    }
    else
        ensure=0xff;
    if(ensure==0x00) {
        //printf("\r\n模块最大指纹容量=%d",p->PS_max);
        //printf("\r\n对比等级=%d",p->PS_level);
        //printf("\r\n地址=%x",p->PS_addr);
        //printf("\r\n波特率=%d",p->PS_N*9600);
    }
    else
        // printf("\r\n%s",this->ensure_message(this,ensure));
        this->ensure_message(this, ensure);
    return ensure;
}
uint8    as608_set_addr( AS608 *this , uint32 addr) {

    uint16  check_byte;
    uint8   ensure;
    uint8   *data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x07 );
    this->send_cmd( 0x15 );
    this->send_byte( addr >> 24 );
    this->send_byte( addr >> 16 );
    this->send_byte( addr >> 8 );
    this->send_byte( addr );

    check_byte  =   0x01 + 0x03 + 0x0F + (u8)(addr >> 24) + (u8)(addr >> 16) + (u8)(addr >> 8) + (u8)addr;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if( data )
        ensure  =   data[9];
    else
        ensure  =   0xFF;
    this->device_address    =   addr;
    if(ensure == 0x00) {}

    //printf("\r\n设置地址成功！");
    else{
        this->ensure_message(this, ensure);
    }

    this->ensure_message(this, ensure);
    return ensure;
}
uint8    as608_valid_templete_num( AS608 *this , uint16 *valid_n ) {

    uint16  check_byte;
    uint8   ensure;
    uint8   *data;

    this->send_head();
    this->send_addr(this->device_address);
    this->send_flag( 0x01 );
    this->send_length( 0x03 );
    this->send_cmd( 0x1d );
    check_byte  =   0x01 + 0x03 + 0x1d;
    this->send_check( check_byte );

    data    =   this->judge_str(this, 2000 );

    if( data ) {
        ensure  =   data[9];
        *valid_n = (data[10]<<8) +data[11];
    }else
        ensure  =   0xFF;
    if(ensure==0x00){}
    //printf("\r\n有效指纹个数=%d",(data[10]<<8)+data[11]);
    else
        this->ensure_message(this, ensure);
    //printf("\r\n%s", );
    this->ensure_message(this, ensure);
    return ensure;
}

uint8    as608_hand_shake( AS608 *this, uint32 addr ) {
    uint16_t count = 4;
    while(count --) {
        this->send_head();
        this->send_addr( this->device_address );
        this->send_byte( 0x01 );
        this->send_byte( 0x00 );
        this->send_byte( 0x00 );
        DELAY_MS(1000);

        if (count == 3)
            scic_msg("信息：握手信号已经送达！等待设备响应.... \n\r");
        else
            scic_msg("信息：再次尝试握手信号已经送达！等待设备响应.... \n\r");
        if ( this->read_flag == true ) {
            break;
        }
    }
    scic_msg("信息：指纹模块失联，重新上电.... \n\r");
    while( this->read_flag == false );

    return true;

}


void    as608_add_finger( AS608* this )
{
    uint8   ensure, process_num = 0;
    uint16  id;
    uint32 k;

    while( true ) {

        switch ( process_num ) {

        case 0:

            scic_msg( "信息：请按下指纹。\n\r" );
            while( TOUCH !=  this->read_state( this ) );
            ensure = this->get_image(this);
            if( ensure == 0x00 ) {
                scic_msg( "信息：得到一个指纹图像，生成特征中。\n\r" );
                ensure  =   this->gen_char(this, CHAR_BUFFER_1);
                if( ensure ==   0x00 ) {
                    scic_msg( "信息：指纹图像获取成功。\n\r" );
                    process_num = 1;
                }else {
                    scic_msg( "信息：指纹图像没有足够的特征\n\r" );
                    this->ensure_message( this, ensure );
                }
            }else {
                this->ensure_message(this, ensure);
            }
            break;

        case 1:
            scic_msg( "信息：请再次按下指纹。\n\r" );
            while( TOUCH !=  this->read_state( this ) );
            ensure = this->get_image(this);
            if( ensure == 0x00 ) {
                ensure  =   this->gen_char(this, CHAR_BUFFER_2);
                if( ensure ==   0x00 ) {
                    scic_msg( "信息：采集到了指纹等待进一步处理。\n\r" );
                    process_num = 2;
                }else {
                    this->ensure_message( this, ensure );
                }
            }else {
                this->ensure_message(this, ensure);
            }
            DELAY_MS(2000);
            break;

        case 2:
            scic_msg( "信息：正在比对采集指纹是否正确 。\n\r" );
            ensure  =   this->match(this);
            if( ensure == 0x00 ) {
                scic_msg( "信息：指纹录入中。\n\r" );
                process_num = 3;
            }else {
                scic_msg( "信息：指纹录入失败。\n\r" );
                process_num = 0;
            }
            DELAY_MS(2000);
            break;

        case 3:
            ensure = this->reg_model( this );
            if( ensure == 0x00 ) {
                scic_msg( "信息：生成指纹模板成功。\n\r" );
                process_num = 4;
            }else {
                process_num = 0;
                this->ensure_message( this, ensure );
            }
            DELAY_MS(2000);

            break;

        case 4:

            ensure  =   this->store_char( this,CHAR_BUFFER_2, id );
            if( ensure == 0x00 ) {
                this->valid_templete_num( this, &this->valid_templete_num );
                scic_msg( "信息：已存储指纹模板。\n\r" );
                return;
            }else {
                this->ensure_message(this, ensure);
            }
            break;

        }

    }


}
extern uint16  error_count;
extern Uint16 id_flag;
void    as608_press_finger( AS608 *this )
{
    uint8   ensure;

    ensure  =   this->get_image( this );
    this->ensure_message( this, ensure );
    if( ensure == 0x00 ) {
        scic_msg( "信息：正在采集指纹图像。\n\r" );
        ensure  =   this->gen_char( this, CHAR_BUFFER_1 );
        this->ensure_message( this, ensure );

        if( ensure == 0x00 ) {
            scic_msg( "信息：正在校验。\n\r" );
            ensure  =   this->high_speed_search( this, CHAR_BUFFER_1, 0,100, &this->search_result );
            if( ensure == 0x00 ) {
                scic_msg( "信息：指纹匹配成功。\n\r" );
                id_flag = true;
                error_count = 0;
            }else {
                error_count ++;
                if( error_count > 3 ) {
                    scic_msg( "信息：验证失败超过3次蜂鸣器噪起来。\n\r" );
                    error_count = 0;
                }else {
                    scic_msg( "信息：校验失败，请重新按指纹，原因 如下：\n\r" );
                }
            }
        }
    }
    DELAY_US(1000);

}


uint8*    as608_ensure_message( AS608 *this ,uint8 ensure) {

    const char *p;

    switch(ensure)
    {
    case  0x00:
        p="信息：OK\r\n";
        break;
    case  0x01:
        p="信息：数据包接收错误\r\n";break;
    case  0x02:
        p="信息：传感器上没有手指\r\n";break;
    case  0x03:
        p="信息：录入指纹图像失败\r\n";break;
    case  0x04:
        p="信息：指纹图像太干、太淡而生不成特征\r\n";break;
    case  0x05:
        p="信息：指纹图像太湿、太糊而生不成特征\r\n";break;
    case  0x06:
        p="信息：指纹图像太乱而生不成特征\r\n";break;
    case  0x07:
        p="信息：指纹图像正常，但特征点太少（或面积太小）而生不成特征\r\n";break;
    case  0x08:
        p="信息：指纹不匹配\r\n";break;
    case  0x09:
        p="信息：没搜索到指纹\r\n";break;
    case  0x0a:
        p="信息：特征合并失败\r\n";break;
    case  0x0b:
        p="信息：访问指纹库时地址序号超出指纹库范围\r\n";
    case  0x10:
        p="信息：删除模板失败\r\n";break;
    case  0x11:
        p="信息：清空指纹库失败\r\n";break;
    case  0x15:
        p="信息：缓冲区内没有有效原始图而生不成图像\r\n";break;
    case  0x18:
        p="信息：读写 FLASH 出错\r\n";break;
    case  0x19:
        p="信息：未定义错误\r\n";break;
    case  0x1a:
        p="信息：无效寄存器号\r\n";break;
    case  0x1b:
        p="信息：寄存器设定内容错误\r\n";break;
    case  0x1c:
        p="信息：记事本页码指定错误\r\n";break;
    case  0x1f:
        p="信息：指纹库满\r\n";break;
    case  0x20:
        p="信息：地址错误\r\n";break;
    default :
        p="信息：模块返回确认码有误\r\n";break;
    }
    scic_msg(p);
    return (uint8*)p;
}

static  uint8*   as608_judge_str( AS608 *this, uint16 wait_time )
{
    int i;
    // wait sci recv interrupt.
    while( this->read_flag == false ) {

    }

    this->read_flag = false;

    return (uint8*)this->callback_str;
}


void    as608_send_head( void ) {
    as608_send_byte( 0xEF );
    as608_send_byte( 0x01 );
}
void    as608_send_addr( uint32 addr ) {

    as608_send_byte( addr >> 24 );
    as608_send_byte( addr >> 16 );
    as608_send_byte( addr >> 8 );
    as608_send_byte( addr );

}
void    as608_send_flag( uint8 flag ) {
    as608_send_byte( flag );
}
void    as608_send_length( uint16 length ) {
    as608_send_byte( length >> 8 );
    as608_send_byte( length );
}
void    as608_send_cmd( uint8 cmd ) {
    as608_send_byte( cmd );
}
void    as608_send_check( uint16 check ) {
    as608_send_byte( check >> 8 );
    as608_send_byte( check );
}

bool    as608_uart_process( struct as608_t *this, BYTE val ) {

    BYTE *data;
    uint8 str[8];
    uint8 length = 0;
    uint8 check_sum,i;
    BYTE  msg[40];

    this->callback_str[ this->recv_count ++ ] = val;
    // check message head.
    if( this->callback_str[0] != 0xEF ){
        memset( this->callback_str,0 ,50 );
        this->recv_count = 0;
        return false ;
    }
    // check number < 9 return
    if( this->recv_count < 9 ) {
        return false;
    }

    // check words.
    str[0] = 0xef;
    str[1] = 0x01;
    str[2] = (this->device_address >> 24) & 0xFF;
    str[3] = (this->device_address >> 16) & 0xFF;
    str[4] = (this->device_address >> 8) &0xff;
    str[5] = this->device_address & 0xff;
    str[6] = 0x07;
    str[7] = '\0';
    // EF 01 FF FF FF FF 07
    if( strstr( (const char*) this->callback_str, (const char*)str )  == NULL ) {
        memset( this->callback_str,0 ,50 );
        this->recv_count = 0;
        return false;
    }
    // get the length,
    length = this->callback_str[8];

    // tail data < length
    if( (this->recv_count - 8) < length ) {
        return false;
    }

    //scic_msg("信息：设备响应完毕，接收到数据开始处理.... \n\r");
    this->recv_count = 0;
    return true;
}
