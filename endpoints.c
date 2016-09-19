#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "coap.h"

static char light = '0';

static char motor = '0';

const uint16_t rsplen = 1500;
static char rsp[1500] = "";
void build_rsp(void);

void endpoint_setup(void)
{
    build_rsp();
}



static const coap_endpoint_path_t path_well_known_core = {2, {".well-known", "core"}};
static int handle_get_well_known_core(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    return coap_make_response(scratch, outpkt, (const uint8_t *)rsp, strlen(rsp), id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_APPLICATION_LINKFORMAT);
}

static const coap_endpoint_path_t path_light = {1, {"light"}};

static const coap_endpoint_path_t path_motor = {1, {"motor"}};


static int handle_get_light(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_TEXT_PLAIN);
}

static int handle_get_motor(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi,
    uint8_t id_lo)
{
    return coap_make_response(scratch, outpkt, (const uint8_t *)&motor, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT,
        COAP_CONTENTTYPE_TEXT_PLAIN);
}



static int handle_put_light(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    if (inpkt->payload.len == 0)
        return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
    if (inpkt->payload.p[0] == 'z')
    {
        light = '1';
        printf("160, 082, 045 ON\n");

        return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else if(inpkt->payload.p[0]=='2'){
        
        printf("205 092 092 ON\n");
        light = '2';
        return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
        
    }
    else if(inpkt->payload.p[0]=='3'){
        
        printf("218 165 032 ON\n");
        light = '3';
        return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else if(inpkt->payload.p[0]=='4'){
        
        printf("250 250 210 ON\n");
        light = '4';
        return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else if (inpkt->payload.p[0]=='5'){
        
        printf("173 255 047 ON\n");
        light = '5';
        return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else if (inpkt->payload.p[0]=='6'){
        
        printf("127 255 212 ON\n");
        light = '6';
        return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else if (inpkt->payload.p[0]=='7'){
        
        printf("238 130 238 ON\n");
        light = '7';
        return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else if (inpkt->payload.p[0]=='8'){
        printf("064 224 208 ON\n");
        light = '8';
        return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    
    
    else
    {
        light = '0';
        printf("OFF\n");

        return coap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
}

static int handle_put_motor(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi,
    uint8_t id_lo)
{
    if (inpkt->payload.len==0) {
        return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    if (inpkt->payload.p[0]=='1') {
        motor = '1';
        printf("Motor 1 on\n");
        
        return coap_make_response(scratch, outpkt, (const uint8_t *)&motor, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else if (inpkt->payload.p[0]=='2'){
        motor = '2';
        printf("Motor 2 on\n");
        
        return coap_make_response(scratch, outpkt, (const uint8_t *)&motor, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED,COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else if (inpkt->payload.p[0]=='2'){
        motor = '3';
        printf("Motor 3 on\n");
        
        return coap_make_response(scratch, outpkt, (const uint8_t *)&motor, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else {
        motor = '0';
        printf("Motor 0 off\n");
        
        return coap_make_response(scratch, outpkt, (const uint8_t *)&motor, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
}

const coap_endpoint_t endpoints[] =
{
    {COAP_METHOD_GET, handle_get_well_known_core, &path_well_known_core, "ct=40"},
    {COAP_METHOD_GET, handle_get_light, &path_light, "ct=0"},
    {COAP_METHOD_PUT, handle_put_light, &path_light, NULL},
    {COAP_METHOD_GET, handle_get_motor, &path_motor, "ct=0"},
    {COAP_METHOD_PUT, handle_put_motor, &path_motor, NULL},
    {(coap_method_t)0, NULL, NULL, NULL}
};

void build_rsp(void)
{
    uint16_t len = rsplen;
    const coap_endpoint_t *ep = endpoints;
    int i;
    
    len--; // Null-terminated string
    
    while(NULL != ep->handler)
    {
        if (NULL == ep->core_attr) {
            ep++;
            continue;
        }
        
        if (0 < strlen(rsp)) {
            strncat(rsp, ",", len);
            len--;
        }
        
        strncat(rsp, "<", len);
        len--;
        
        for (i = 0; i < ep->path->count; i++) {
            strncat(rsp, "/", len);
            len--;
            
            strncat(rsp, ep->path->elems[i], len);
            len -= strlen(ep->path->elems[i]);
        }
        
        strncat(rsp, ">;", len);
        len -= 2;
        
        strncat(rsp, ep->core_attr, len);
        len -= strlen(ep->core_attr);
        
        ep++;
    }
}

