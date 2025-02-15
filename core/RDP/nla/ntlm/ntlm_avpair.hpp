/*
    This program is free software; you can redistribute it and/or modify it
     under the terms of the GNU General Public License as published by the
     Free Software Foundation; either version 2 of the License, or (at your
     option) any later version.

    This program is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
     Public License for more details.

    You should have received a copy of the GNU General Public License along
     with this program; if not, write to the Free Software Foundation, Inc.,
     675 Mass Ave, Cambridge, MA 02139, USA.

    Product name: redemption, a FLOSS RDP proxy
    Copyright (C) Wallix 2013
    Author(s): Christophe Grosjean, Raphael Zhou, Meng Tan
*/
#ifndef _REDEMPTION_CORE_RDP_NLA_NTLM_NTLMAVPAIR_HPP_
#define _REDEMPTION_CORE_RDP_NLA_NTLM_NTLMAVPAIR_HPP_

#include "log.hpp"
#include "stream.hpp"

// 2.2.2.1   AV_PAIR
// ==================================
// The AV_PAIR structure defines an attribute/value pair. Sequences of AV_PAIR
//  structures are used in the CHALLENGE_MESSAGE (section 2.2.1.2) and
//  AUTHENTICATE_MESSAGE (section 2.2.1.3) messages.

//  Although the following figure suggests that the most significant bit (MSB) of AvId
//  is aligned with the MSB of a 32-bit word, an AV_PAIR can be aligned on any byte
//  boundary and can be 4+N bytes long for arbitrary N (N = the contents of AvLen).

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// | | | | | | | | | | |1| | | | | | | | | |2| | | | | | | | | |3| |
// |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |              AvId             |             AvLen             |
// +---------------+---------------+---------------+---------------+
// |                         Value (variable)                      |
// +---------------+---------------+---------------+---------------+
// |                              ...                              |
// +---------------+---------------+---------------+---------------+

// AvId (2 bytes):  A 16-bit unsigned integer that defines the information type in the
//  Value field. The contents of this field MUST be one of the values from the following
//  table.The corresponding Value field in this AV_PAIR MUST contain the information
//  specified in the description of that AvId.
// +----------------------+-------------------------------------------------------------+
// | Value                | Meaning                                                     |
// +----------------------+-------------------------------------------------------------+
// | MsvAvEOL             | Indicates that this is the last AV_PAIR in the list. AvLen  |
// |                      |  MUST be 0. This type of information MUST be present in     |
// |                      |  the AV pair list.                                          |
// +----------------------+-------------------------------------------------------------+
// | MsvAvNbComputerName  | The server's NetBIOS computer name. The name MUST be in     |
// |                      |  Unicode, and is not null-terminated. This type of          |
// |                      |  information MUST be present in the AV_pair list.           |
// +----------------------+-------------------------------------------------------------+
// | MsvAvNbDomainName    | The server's NetBIOS domain name. The name MUST be in       |
// |                      |  Unicode, and is not null-terminated. This type of          |
// |                      |  information MUST be present in the AV_pair list.           |
// +----------------------+-------------------------------------------------------------+
// | MsvAvDnsComputerName | The fully qualified domain name (FQDN (1)) of the computer. |
// |                      |  The name MUST be in Unicode, and is not null-terminated.   |
// +----------------------+-------------------------------------------------------------+
// | MsvAvDnsDomainName   | The FQDN (2) of the domain. The name MUST be in Unicode,    |
// |                      |  and is not null-terminated.                                |
// +----------------------+-------------------------------------------------------------+
// | MsvAvDnsTreeName     | The FQDN (2) of the forest. The name MUST be in Unicode,    |
// |                      |  and is not null-terminated.                                |
// +----------------------+-------------------------------------------------------------+
// | MsvAvFlags           | A 32-bit value indicating server or client configuration.   |
// | 0x0006               | 0x00000001: indicates to the client that the account        |
// |                      |  authentication is constrained.                             |
// |                      | 0x00000001: indicates to the client that the account        |
// |                      |  authentication is constrained.                             |
// |                      | 0x00000002: indicates that the client is providing message  |
// |                      |  integrity in the MIC field (section 2.2.1.3) in the        |
// |                      |  AUTHENTICATE_MESSAGE.                                      |
// |                      | 0x00000004: indicates that the client is providing a        |
// |                      |  target SPN generated from an untrusted source.             |
// +----------------------+-------------------------------------------------------------+
// | MsvAvTimeStamp       | A FILETIME structure ([MS-DTYP] section 2.3.3) in little    |
// | 0x0007               |  -endian byte order that contains the server local time.    |
// +----------------------+-------------------------------------------------------------+
// | MsvAvSingleHost      | A Single_Host_Data (section 2.2.2.2) structure. The Value   |
// | 0x0008               |  field contains a platform-specific blob, as well as a      |
// |                      |  MachineID created at computer startup to identify the      |
// |                      |  calling machine.                                           |
// +----------------------+-------------------------------------------------------------+
// | MsvAvTargetName      | The SPN of the target server. The name MUST be in Unicode   |
// | 0x0009               |  and is not null-terminated.                                |
// +----------------------+-------------------------------------------------------------+
// | MsvChannelBindings   | A channel bindings hash. The Value field contains an MD5    |
// | 0x000A               |  hash ([RFC4121] section 4.1.1.2) of a                      |
// |                      |  gss_channel_bindings_struct ([RFC2744] section 3.11).      |
// |                      |  An all-zero value of the hash is used to indicate absence  |
// |                      |  of channel bindings.                                       |
// +----------------------+-------------------------------------------------------------+


// AvLen (2 bytes):  A 16-bit unsigned integer that defines the length, in bytes, of
//  the Value field.
// Value (variable):  A variable-length byte-array that contains the value defined for
//  this AV pair entry. The contents of this field depend on the type expressed in the
//  AvId field. The available types and resulting format and contents of this field are
//  specified in the table within the AvId field description in this topic.
enum NTLM_AV_ID {
    MsvAvEOL = 0x0000,
    MsvAvNbComputerName,
    MsvAvNbDomainName,
    MsvAvDnsComputerName,
    MsvAvDnsDomainName,
    MsvAvDnsTreeName,
    MsvAvFlags,
    MsvAvTimestamp,
    MsvAvSingleHost,
    MsvAvTargetName,
    MsvChannelBindings,
    AV_ID_MAX
};

struct NtlmAvPair {
    uint16_t AvId;
    uint16_t AvLen;
    BStream Value;

    NtlmAvPair(NTLM_AV_ID id, const uint8_t * value, size_t length)
        : AvId(id)
        , AvLen(length)
        , Value(length)
    {
        if (value) {
            this->Value.out_copy_bytes(value, length);
            this->Value.mark_end();
            this->Value.rewind();
        }
    }

    void emit(Stream & stream) {
        stream.out_uint16_le(this->AvId);
        stream.out_uint16_le(this->AvLen);
        stream.out_copy_bytes(this->Value.get_data(), this->Value.size());
    }

    // void recv(Stream & stream) {
    //     this->AvId = stream.in_uint16_le();
    //     this->AvLen = stream.in_uint16_le();
    //     this->Value.init(this->AvLen);
    //     this->Value.out_copy_bytes(stream.p, this->AvLen);
    //     this->Value.mark_end();
    //     this->Value.rewind();
    //     stream.in_skip_bytes(this->AvLen);
    // }

    void print() {
        LOG(LOG_INFO, "\tAvId: 0x%02X, AvLen : %u,", this->AvId, this->AvLen);
        this->Value.print();
    }
};

struct NtlmAvPairList {
    NtlmAvPair * list[AV_ID_MAX];

    NtlmAvPairList() {
        for (int i = 0; i < AV_ID_MAX; i++) {
            this->list[i] = NULL;
        }
        this->list[MsvAvEOL] = new NtlmAvPair(MsvAvEOL, NULL, 0);
    }

    virtual ~NtlmAvPairList() {
        for (int i = 0; i < AV_ID_MAX; i++) {
            delete this->list[i];
        }
    }

    void add(NTLM_AV_ID avId, const uint8_t * value, size_t length) {
        if (this->list[avId])
            delete this->list[avId];
        this->list[avId] = new NtlmAvPair(avId, value, length);
    }

    bool rm(NTLM_AV_ID avId) {
        // ASSUME avID != MsvAvEOL
        bool res = false;
        if (this->list[avId]) {
            delete this->list[avId];
            this->list[avId] = NULL;
            res = true;
        }
        return res;
    }

    size_t length() {
        size_t res = 0;
        for (int i = 0; i < AV_ID_MAX; i++) {
            if (this->list[i]) {
                res++;
            }
        }
        return res;
    }

    size_t packet_length() {
        size_t res = 0;
        for (int i = 0; i < AV_ID_MAX; i++) {
            if (this->list[i]) {
                res += sizeof(this->list[i]->AvId);
                res += sizeof(this->list[i]->AvLen);
                // res += 4;
                res += this->list[i]->AvLen;
            }
        }
        return res;
    }

    void emit(Stream & stream) {
        for (int i = 1; i < AV_ID_MAX; i++) {
            if (this->list[i]) {
                this->list[i]->emit(stream);
            }
        }
        // ASSUME this->list[MsvAvEOL] != NULL
        this->list[MsvAvEOL]->emit(stream);
        stream.mark_end();
    }

    void recv(Stream & stream) {
        for (int i = 0; i < AV_ID_MAX; i++) {
            NTLM_AV_ID id = static_cast<NTLM_AV_ID>(stream.in_uint16_le());
            uint16_t length = stream.in_uint16_le();
            if (id == MsvAvEOL) {
                // ASSUME last element is MsvAvEOL
                stream.in_skip_bytes(length);
                break;
            }
            this->add(id, stream.p, length);
            stream.in_skip_bytes(length);
        }
    }

    void print() {
        LOG(LOG_INFO, "Av Pair List : %zu elements {", this->length());

        for (int i = 0; i < AV_ID_MAX; i++) {
            if (this->list[i]) {
                this->list[i]->print();
            }
        }

        LOG(LOG_INFO, "}");
    }


};



#endif
