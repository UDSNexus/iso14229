#include "tp.h"
#include <assert.h>

/**
 * @brief
 *
 * @param hdl
 * @param info, if NULL, the default values are used:
 *   A_Mtype: message type (diagnostic (DEFAULT), remote diagnostic, secure diagnostic, secure
 * remote diagnostic)
 * A_TA_Type: application target address type (physical (DEFAULT) or functional)
 * A_SA: unused
 * A_TA: unused
 * A_AE: unused
 * @return ssize_t
 */
ssize_t UDSTpGetSendBuf(struct UDSTpHandle *hdl, uint8_t **buf) {
    assert(hdl);
    assert(hdl->get_send_buf);
    return hdl->get_send_buf(hdl, buf);
}
ssize_t UDSTpSend(struct UDSTpHandle *hdl, const uint8_t *buf, ssize_t len, UDSSDU_t *info) {
    assert(hdl);
    assert(hdl->send);
    return hdl->send(hdl, (uint8_t *)buf, len, info);
}

UDSTpStatus_t UDSTpPoll(struct UDSTpHandle *hdl) {
    assert(hdl);
    assert(hdl->poll);
    return hdl->poll(hdl);
}

ssize_t UDSTpPeek(struct UDSTpHandle *hdl, uint8_t **buf, UDSSDU_t *info) {
    assert(hdl);
    assert(hdl->peek);
    return hdl->peek(hdl, buf, info);
}

const uint8_t *UDSTpGetRecvBuf(struct UDSTpHandle *hdl, size_t *p_len) {
    assert(hdl);
    ssize_t len = 0;
    uint8_t *buf = NULL;
    len = UDSTpPeek(hdl, &buf, NULL);
    if (len > 0) {
        if (p_len) {
            *p_len = len;
        }
        return buf;
    } else {
        return NULL;
    }
}

size_t UDSTpGetRecvLen(UDSTpHandle_t *hdl) {
    assert(hdl);
    size_t len = 0;
    UDSTpGetRecvBuf(hdl, &len);
    return len;
}

void UDSTpAckRecv(UDSTpHandle_t *hdl) {
    assert(hdl);
    hdl->ack_recv(hdl);
}
