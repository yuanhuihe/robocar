
#line 1 "DataScanner.rl"
/* 
 * ragel -G2  -o scanner.cpp DataScanner.rl 
 */
#include "_inl.hpp"
#include <iostream>
    
#line 58 "DataScanner.rl"


    
#line 14 "scanner.cpp"
static const int fast_cmp_start = 227;
static const int fast_cmp_first_final = 227;
static const int fast_cmp_error = 0;

static const int fast_cmp_en_main = 227;


#line 61 "DataScanner.rl"

    class Scan
    {
        public:
            void init()
            {
                type = 0;
                
#line 31 "scanner.cpp"
	{
	cs = fast_cmp_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 69 "DataScanner.rl"
            }
            int execute(const char* data)
            {
                const char* p = data;
                const char* pe = data + strlen(p)+1;
                const char* eof = pe;
                
#line 47 "scanner.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr3:
#line 25 "DataScanner.rl"
	{te = p+1;{ type = DATA_CMD; {p++; cs = 227; goto _out;} }}
	goto st227;
tr4:
#line 12 "DataScanner.rl"
	{te = p+1;{ type = DEV_CTR; {p++; cs = 227; goto _out;} }}
	goto st227;
tr7:
#line 26 "DataScanner.rl"
	{te = p+1;{ type = DATA_DATA; {p++; cs = 227; goto _out;} }}
	goto st227;
tr10:
#line 15 "DataScanner.rl"
	{te = p+1;{ type = DEV_HMU; {p++; cs = 227; goto _out;} }}
	goto st227;
tr11:
#line 16 "DataScanner.rl"
	{te = p+1;{ type = DEV_Hi5; {p++; cs = 227; goto _out;} }}
	goto st227;
tr13:
#line 18 "DataScanner.rl"
	{te = p+1;{ type = DEV_IMU; {p++; cs = 227; goto _out;} }}
	goto st227;
tr15:
#line 19 "DataScanner.rl"
	{te = p+1;{ type = DEV_MTV; {p++; cs = 227; goto _out;} }}
	goto st227;
tr17:
#line 13 "DataScanner.rl"
	{te = p+1;{ type = DEV_NEU; {p++; cs = 227; goto _out;} }}
	goto st227;
tr19:
#line 20 "DataScanner.rl"
	{te = p+1;{ type = DEV_PC;  {p++; cs = 227; goto _out;} }}
	goto st227;
tr20:
#line 21 "DataScanner.rl"
	{te = p+1;{ type = DEV_P2P; {p++; cs = 227; goto _out;} }}
	goto st227;
tr21:
#line 14 "DataScanner.rl"
	{te = p+1;{ type = DEV_QR;  {p++; cs = 227; goto _out;} }}
	goto st227;
tr24:
#line 22 "DataScanner.rl"
	{te = p+1;{ type = DEV_SDK; {p++; cs = 227; goto _out;} }}
	goto st227;
tr26:
#line 27 "DataScanner.rl"
	{te = p+1;{ type = DATA_STAT; {p++; cs = 227; goto _out;} }}
	goto st227;
tr28:
#line 17 "DataScanner.rl"
	{te = p+1;{ type = DEV_Wii; {p++; cs = 227; goto _out;} }}
	goto st227;
tr46:
#line 50 "DataScanner.rl"
	{te = p+1;{ type =  FPC_BtSyncID; {p++; cs = 227; goto _out;} }}
	goto st227;
tr60:
#line 53 "DataScanner.rl"
	{te = p+1;{ type =  FPC_ConfigConfirm ; {p++; cs = 227; goto _out;} }}
	goto st227;
tr70:
#line 46 "DataScanner.rl"
	{te = p+1;{ type =  FPC_DetailRep; {p++; cs = 227; goto _out;} }}
	goto st227;
tr78:
#line 52 "DataScanner.rl"
	{te = p+1;{ type =  FPC_Evasive; {p++; cs = 227; goto _out;} }}
	goto st227;
tr88:
#line 45 "DataScanner.rl"
	{te = p+1;{ type =  FPC_HeartBeat; {p++; cs = 227; goto _out;} }}
	goto st227;
tr100:
#line 47 "DataScanner.rl"
	{te = p+1;{ type =  FPC_JoinConfirm; {p++; cs = 227; goto _out;} }}
	goto st227;
tr106:
#line 51 "DataScanner.rl"
	{te = p+1;{ type =  FPC_Leave;   {p++; cs = 227; goto _out;} }}
	goto st227;
tr118:
#line 48 "DataScanner.rl"
	{te = p+1;{ type =  FPC_SyncConfig;  {p++; cs = 227; goto _out;} }}
	goto st227;
tr122:
#line 49 "DataScanner.rl"
	{te = p+1;{ type =  FPC_SyncReq;  {p++; cs = 227; goto _out;} }}
	goto st227;
tr146:
#line 42 "DataScanner.rl"
	{te = p+1;{ type =  FPS_AppPathChange;  {p++; cs = 227; goto _out;} }}
	goto st227;
tr160:
#line 41 "DataScanner.rl"
	{te = p+1;{ type =  FPS_BtSyncCancel;   {p++; cs = 227; goto _out;} }}
	goto st227;
tr165:
#line 38 "DataScanner.rl"
	{te = p+1;{ type =  FPS_BtSyncNeed; {p++; cs = 227; goto _out;} }}
	goto st227;
tr174:
#line 40 "DataScanner.rl"
	{te = p+1;{ type =  FPS_BtSyncComplete; {p++; cs = 227; goto _out;} }}
	goto st227;
tr179:
#line 39 "DataScanner.rl"
	{te = p+1;{ type =  FPS_BtSyncConfig; {p++; cs = 227; goto _out;} }}
	goto st227;
tr186:
#line 35 "DataScanner.rl"
	{te = p+1;{ type =  FPS_Config;     {p++; cs = 227; goto _out;} }}
	goto st227;
tr196:
#line 32 "DataScanner.rl"
	{te = p+1;{ type =  FPS_DetailReq;  {p++; cs = 227; goto _out;} }}
	goto st227;
tr206:
#line 30 "DataScanner.rl"
	{te = p+1;{ type =  FPS_HeartBeat ; {p++; cs = 227; goto _out;} }}
	goto st227;
tr216:
#line 33 "DataScanner.rl"
	{te = p+1;{ type =  FPS_JoinGroup;  {p++; cs = 227; goto _out;} }}
	goto st227;
tr227:
#line 37 "DataScanner.rl"
	{te = p+1;{ type =  FPS_LeaveGroup; {p++; cs = 227; goto _out;} }}
	goto st227;
tr236:
#line 31 "DataScanner.rl"
	{te = p+1;{ type =  FPS_PeerStat;   {p++; cs = 227; goto _out;} }}
	goto st227;
tr246:
#line 34 "DataScanner.rl"
	{te = p+1;{ type =  FPS_SyncNeed;   {p++; cs = 227; goto _out;} }}
	goto st227;
tr250:
#line 36 "DataScanner.rl"
	{te = p+1;{ type =  FPS_SyncRep;    {p++; cs = 227; goto _out;} }}
	goto st227;
tr264:
#line 55 "DataScanner.rl"
	{te = p;p--;}
	goto st227;
st227:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof227;
case 227:
#line 1 "NONE"
	{ts = p;}
#line 209 "scanner.cpp"
	switch( (*p) ) {
		case 32: goto st228;
		case 67: goto st1;
		case 68: goto st4;
		case 72: goto st7;
		case 73: goto st10;
		case 77: goto st12;
		case 78: goto st14;
		case 80: goto st16;
		case 81: goto st18;
		case 83: goto st19;
		case 87: goto st23;
		case 99: goto st25;
		case 115: goto st111;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st228;
	goto st0;
st0:
cs = 0;
	goto _out;
st228:
	if ( ++p == pe )
		goto _test_eof228;
case 228:
	if ( (*p) == 32 )
		goto st228;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st228;
	goto tr264;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 77: goto st2;
		case 84: goto st3;
	}
	goto st0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 68 )
		goto tr3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 82 )
		goto tr4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 65 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 84 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 65 )
		goto tr7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 77: goto st8;
		case 105: goto st9;
	}
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 85 )
		goto tr10;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 53 )
		goto tr11;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 77 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 85 )
		goto tr13;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( (*p) == 84 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 86 )
		goto tr15;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 69 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 85 )
		goto tr17;
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 50: goto st17;
		case 67: goto tr19;
	}
	goto st0;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 80 )
		goto tr20;
	goto st0;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	if ( (*p) == 82 )
		goto tr21;
	goto st0;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 68: goto st20;
		case 84: goto st21;
	}
	goto st0;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) == 75 )
		goto tr24;
	goto st0;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	if ( (*p) == 65 )
		goto st22;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 84 )
		goto tr26;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( (*p) == 105 )
		goto st24;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	if ( (*p) == 105 )
		goto tr28;
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	if ( (*p) == 45 )
		goto st26;
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 98: goto st27;
		case 99: goto st36;
		case 100: goto st50;
		case 101: goto st60;
		case 104: goto st68;
		case 106: goto st78;
		case 108: goto st90;
		case 115: goto st96;
	}
	goto st0;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	if ( (*p) == 116 )
		goto st28;
	goto st0;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	if ( (*p) == 115 )
		goto st29;
	goto st0;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	if ( (*p) == 121 )
		goto st30;
	goto st0;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	if ( (*p) == 110 )
		goto st31;
	goto st0;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	if ( (*p) == 99 )
		goto st32;
	goto st0;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	if ( (*p) == 105 )
		goto st33;
	goto st0;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	if ( (*p) == 100 )
		goto st34;
	goto st0;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	if ( (*p) == 45 )
		goto st35;
	goto st0;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	if ( (*p) == 99 )
		goto tr46;
	goto st0;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	if ( (*p) == 111 )
		goto st37;
	goto st0;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	if ( (*p) == 110 )
		goto st38;
	goto st0;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	if ( (*p) == 102 )
		goto st39;
	goto st0;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	if ( (*p) == 105 )
		goto st40;
	goto st0;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	if ( (*p) == 103 )
		goto st41;
	goto st0;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	if ( (*p) == 99 )
		goto st42;
	goto st0;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	if ( (*p) == 111 )
		goto st43;
	goto st0;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	if ( (*p) == 110 )
		goto st44;
	goto st0;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	if ( (*p) == 102 )
		goto st45;
	goto st0;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	if ( (*p) == 105 )
		goto st46;
	goto st0;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	if ( (*p) == 114 )
		goto st47;
	goto st0;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	if ( (*p) == 109 )
		goto st48;
	goto st0;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	if ( (*p) == 45 )
		goto st49;
	goto st0;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	if ( (*p) == 99 )
		goto tr60;
	goto st0;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	if ( (*p) == 101 )
		goto st51;
	goto st0;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	if ( (*p) == 116 )
		goto st52;
	goto st0;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	if ( (*p) == 97 )
		goto st53;
	goto st0;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	if ( (*p) == 105 )
		goto st54;
	goto st0;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	if ( (*p) == 108 )
		goto st55;
	goto st0;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	if ( (*p) == 114 )
		goto st56;
	goto st0;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	if ( (*p) == 101 )
		goto st57;
	goto st0;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	if ( (*p) == 112 )
		goto st58;
	goto st0;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	if ( (*p) == 45 )
		goto st59;
	goto st0;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	if ( (*p) == 99 )
		goto tr70;
	goto st0;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	if ( (*p) == 118 )
		goto st61;
	goto st0;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	if ( (*p) == 97 )
		goto st62;
	goto st0;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	if ( (*p) == 115 )
		goto st63;
	goto st0;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	if ( (*p) == 105 )
		goto st64;
	goto st0;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	if ( (*p) == 118 )
		goto st65;
	goto st0;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	if ( (*p) == 101 )
		goto st66;
	goto st0;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	if ( (*p) == 45 )
		goto st67;
	goto st0;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	if ( (*p) == 99 )
		goto tr78;
	goto st0;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	if ( (*p) == 101 )
		goto st69;
	goto st0;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	if ( (*p) == 97 )
		goto st70;
	goto st0;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	if ( (*p) == 114 )
		goto st71;
	goto st0;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	if ( (*p) == 116 )
		goto st72;
	goto st0;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	if ( (*p) == 98 )
		goto st73;
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	if ( (*p) == 101 )
		goto st74;
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	if ( (*p) == 97 )
		goto st75;
	goto st0;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) == 116 )
		goto st76;
	goto st0;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	if ( (*p) == 45 )
		goto st77;
	goto st0;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 99 )
		goto tr88;
	goto st0;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	if ( (*p) == 111 )
		goto st79;
	goto st0;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	if ( (*p) == 105 )
		goto st80;
	goto st0;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	if ( (*p) == 110 )
		goto st81;
	goto st0;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	if ( (*p) == 99 )
		goto st82;
	goto st0;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	if ( (*p) == 111 )
		goto st83;
	goto st0;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	if ( (*p) == 110 )
		goto st84;
	goto st0;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	if ( (*p) == 102 )
		goto st85;
	goto st0;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	if ( (*p) == 105 )
		goto st86;
	goto st0;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	if ( (*p) == 114 )
		goto st87;
	goto st0;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	if ( (*p) == 109 )
		goto st88;
	goto st0;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	if ( (*p) == 45 )
		goto st89;
	goto st0;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	if ( (*p) == 99 )
		goto tr100;
	goto st0;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	if ( (*p) == 101 )
		goto st91;
	goto st0;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	if ( (*p) == 97 )
		goto st92;
	goto st0;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	if ( (*p) == 118 )
		goto st93;
	goto st0;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	if ( (*p) == 101 )
		goto st94;
	goto st0;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	if ( (*p) == 45 )
		goto st95;
	goto st0;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	if ( (*p) == 99 )
		goto tr106;
	goto st0;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) == 121 )
		goto st97;
	goto st0;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	if ( (*p) == 110 )
		goto st98;
	goto st0;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	if ( (*p) == 99 )
		goto st99;
	goto st0;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 99: goto st100;
		case 114: goto st107;
	}
	goto st0;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	if ( (*p) == 111 )
		goto st101;
	goto st0;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	if ( (*p) == 110 )
		goto st102;
	goto st0;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	if ( (*p) == 102 )
		goto st103;
	goto st0;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	if ( (*p) == 105 )
		goto st104;
	goto st0;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	if ( (*p) == 103 )
		goto st105;
	goto st0;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	if ( (*p) == 45 )
		goto st106;
	goto st0;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	if ( (*p) == 99 )
		goto tr118;
	goto st0;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	if ( (*p) == 101 )
		goto st108;
	goto st0;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	if ( (*p) == 113 )
		goto st109;
	goto st0;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	if ( (*p) == 45 )
		goto st110;
	goto st0;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	if ( (*p) == 99 )
		goto tr122;
	goto st0;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	if ( (*p) == 45 )
		goto st112;
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	switch( (*p) ) {
		case 97: goto st113;
		case 98: goto st127;
		case 99: goto st157;
		case 100: goto st164;
		case 104: goto st174;
		case 106: goto st184;
		case 108: goto st194;
		case 112: goto st205;
		case 115: goto st214;
	}
	goto st0;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	if ( (*p) == 112 )
		goto st114;
	goto st0;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	if ( (*p) == 112 )
		goto st115;
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	if ( (*p) == 112 )
		goto st116;
	goto st0;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	if ( (*p) == 97 )
		goto st117;
	goto st0;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	if ( (*p) == 116 )
		goto st118;
	goto st0;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	if ( (*p) == 104 )
		goto st119;
	goto st0;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	if ( (*p) == 99 )
		goto st120;
	goto st0;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	if ( (*p) == 104 )
		goto st121;
	goto st0;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	if ( (*p) == 97 )
		goto st122;
	goto st0;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	if ( (*p) == 110 )
		goto st123;
	goto st0;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	if ( (*p) == 103 )
		goto st124;
	goto st0;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	if ( (*p) == 101 )
		goto st125;
	goto st0;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	if ( (*p) == 45 )
		goto st126;
	goto st0;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	if ( (*p) == 115 )
		goto tr146;
	goto st0;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	if ( (*p) == 116 )
		goto st128;
	goto st0;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
	if ( (*p) == 115 )
		goto st129;
	goto st0;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	if ( (*p) == 121 )
		goto st130;
	goto st0;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	if ( (*p) == 110 )
		goto st131;
	goto st0;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	if ( (*p) == 99 )
		goto st132;
	goto st0;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
	switch( (*p) ) {
		case 97: goto st133;
		case 110: goto st139;
		case 111: goto st144;
	}
	goto st0;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	if ( (*p) == 110 )
		goto st134;
	goto st0;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
	if ( (*p) == 99 )
		goto st135;
	goto st0;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	if ( (*p) == 101 )
		goto st136;
	goto st0;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
	if ( (*p) == 108 )
		goto st137;
	goto st0;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
	if ( (*p) == 45 )
		goto st138;
	goto st0;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
	if ( (*p) == 115 )
		goto tr160;
	goto st0;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
	if ( (*p) == 101 )
		goto st140;
	goto st0;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
	if ( (*p) == 101 )
		goto st141;
	goto st0;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
	if ( (*p) == 100 )
		goto st142;
	goto st0;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
	if ( (*p) == 45 )
		goto st143;
	goto st0;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
	if ( (*p) == 115 )
		goto tr165;
	goto st0;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	switch( (*p) ) {
		case 109: goto st145;
		case 110: goto st152;
	}
	goto st0;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	if ( (*p) == 112 )
		goto st146;
	goto st0;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
	if ( (*p) == 108 )
		goto st147;
	goto st0;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
	if ( (*p) == 101 )
		goto st148;
	goto st0;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
	if ( (*p) == 116 )
		goto st149;
	goto st0;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
	if ( (*p) == 101 )
		goto st150;
	goto st0;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
	if ( (*p) == 45 )
		goto st151;
	goto st0;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
	if ( (*p) == 115 )
		goto tr174;
	goto st0;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
	if ( (*p) == 102 )
		goto st153;
	goto st0;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	if ( (*p) == 105 )
		goto st154;
	goto st0;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
	if ( (*p) == 103 )
		goto st155;
	goto st0;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
	if ( (*p) == 45 )
		goto st156;
	goto st0;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
	if ( (*p) == 115 )
		goto tr179;
	goto st0;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	if ( (*p) == 111 )
		goto st158;
	goto st0;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
	if ( (*p) == 110 )
		goto st159;
	goto st0;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
	if ( (*p) == 102 )
		goto st160;
	goto st0;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
	if ( (*p) == 105 )
		goto st161;
	goto st0;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
	if ( (*p) == 103 )
		goto st162;
	goto st0;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
	if ( (*p) == 45 )
		goto st163;
	goto st0;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
	if ( (*p) == 115 )
		goto tr186;
	goto st0;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
	if ( (*p) == 101 )
		goto st165;
	goto st0;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
	if ( (*p) == 116 )
		goto st166;
	goto st0;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
	if ( (*p) == 97 )
		goto st167;
	goto st0;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
	if ( (*p) == 105 )
		goto st168;
	goto st0;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
	if ( (*p) == 108 )
		goto st169;
	goto st0;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
	if ( (*p) == 114 )
		goto st170;
	goto st0;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
	if ( (*p) == 101 )
		goto st171;
	goto st0;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
	if ( (*p) == 113 )
		goto st172;
	goto st0;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
	if ( (*p) == 45 )
		goto st173;
	goto st0;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
	if ( (*p) == 115 )
		goto tr196;
	goto st0;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
	if ( (*p) == 101 )
		goto st175;
	goto st0;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
	if ( (*p) == 97 )
		goto st176;
	goto st0;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
	if ( (*p) == 114 )
		goto st177;
	goto st0;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
	if ( (*p) == 116 )
		goto st178;
	goto st0;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
	if ( (*p) == 98 )
		goto st179;
	goto st0;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
	if ( (*p) == 101 )
		goto st180;
	goto st0;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
	if ( (*p) == 97 )
		goto st181;
	goto st0;
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
	if ( (*p) == 116 )
		goto st182;
	goto st0;
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
	if ( (*p) == 45 )
		goto st183;
	goto st0;
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
	if ( (*p) == 115 )
		goto tr206;
	goto st0;
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
	if ( (*p) == 111 )
		goto st185;
	goto st0;
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
	if ( (*p) == 105 )
		goto st186;
	goto st0;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
	if ( (*p) == 110 )
		goto st187;
	goto st0;
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
	if ( (*p) == 103 )
		goto st188;
	goto st0;
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
	if ( (*p) == 114 )
		goto st189;
	goto st0;
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
	if ( (*p) == 111 )
		goto st190;
	goto st0;
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
	if ( (*p) == 117 )
		goto st191;
	goto st0;
st191:
	if ( ++p == pe )
		goto _test_eof191;
case 191:
	if ( (*p) == 112 )
		goto st192;
	goto st0;
st192:
	if ( ++p == pe )
		goto _test_eof192;
case 192:
	if ( (*p) == 45 )
		goto st193;
	goto st0;
st193:
	if ( ++p == pe )
		goto _test_eof193;
case 193:
	if ( (*p) == 115 )
		goto tr216;
	goto st0;
st194:
	if ( ++p == pe )
		goto _test_eof194;
case 194:
	if ( (*p) == 101 )
		goto st195;
	goto st0;
st195:
	if ( ++p == pe )
		goto _test_eof195;
case 195:
	if ( (*p) == 97 )
		goto st196;
	goto st0;
st196:
	if ( ++p == pe )
		goto _test_eof196;
case 196:
	if ( (*p) == 118 )
		goto st197;
	goto st0;
st197:
	if ( ++p == pe )
		goto _test_eof197;
case 197:
	if ( (*p) == 101 )
		goto st198;
	goto st0;
st198:
	if ( ++p == pe )
		goto _test_eof198;
case 198:
	if ( (*p) == 103 )
		goto st199;
	goto st0;
st199:
	if ( ++p == pe )
		goto _test_eof199;
case 199:
	if ( (*p) == 114 )
		goto st200;
	goto st0;
st200:
	if ( ++p == pe )
		goto _test_eof200;
case 200:
	if ( (*p) == 111 )
		goto st201;
	goto st0;
st201:
	if ( ++p == pe )
		goto _test_eof201;
case 201:
	if ( (*p) == 117 )
		goto st202;
	goto st0;
st202:
	if ( ++p == pe )
		goto _test_eof202;
case 202:
	if ( (*p) == 112 )
		goto st203;
	goto st0;
st203:
	if ( ++p == pe )
		goto _test_eof203;
case 203:
	if ( (*p) == 45 )
		goto st204;
	goto st0;
st204:
	if ( ++p == pe )
		goto _test_eof204;
case 204:
	if ( (*p) == 115 )
		goto tr227;
	goto st0;
st205:
	if ( ++p == pe )
		goto _test_eof205;
case 205:
	if ( (*p) == 101 )
		goto st206;
	goto st0;
st206:
	if ( ++p == pe )
		goto _test_eof206;
case 206:
	if ( (*p) == 101 )
		goto st207;
	goto st0;
st207:
	if ( ++p == pe )
		goto _test_eof207;
case 207:
	if ( (*p) == 114 )
		goto st208;
	goto st0;
st208:
	if ( ++p == pe )
		goto _test_eof208;
case 208:
	if ( (*p) == 115 )
		goto st209;
	goto st0;
st209:
	if ( ++p == pe )
		goto _test_eof209;
case 209:
	if ( (*p) == 116 )
		goto st210;
	goto st0;
st210:
	if ( ++p == pe )
		goto _test_eof210;
case 210:
	if ( (*p) == 97 )
		goto st211;
	goto st0;
st211:
	if ( ++p == pe )
		goto _test_eof211;
case 211:
	if ( (*p) == 116 )
		goto st212;
	goto st0;
st212:
	if ( ++p == pe )
		goto _test_eof212;
case 212:
	if ( (*p) == 45 )
		goto st213;
	goto st0;
st213:
	if ( ++p == pe )
		goto _test_eof213;
case 213:
	if ( (*p) == 115 )
		goto tr236;
	goto st0;
st214:
	if ( ++p == pe )
		goto _test_eof214;
case 214:
	if ( (*p) == 121 )
		goto st215;
	goto st0;
st215:
	if ( ++p == pe )
		goto _test_eof215;
case 215:
	if ( (*p) == 110 )
		goto st216;
	goto st0;
st216:
	if ( ++p == pe )
		goto _test_eof216;
case 216:
	if ( (*p) == 99 )
		goto st217;
	goto st0;
st217:
	if ( ++p == pe )
		goto _test_eof217;
case 217:
	switch( (*p) ) {
		case 110: goto st218;
		case 114: goto st223;
	}
	goto st0;
st218:
	if ( ++p == pe )
		goto _test_eof218;
case 218:
	if ( (*p) == 101 )
		goto st219;
	goto st0;
st219:
	if ( ++p == pe )
		goto _test_eof219;
case 219:
	if ( (*p) == 101 )
		goto st220;
	goto st0;
st220:
	if ( ++p == pe )
		goto _test_eof220;
case 220:
	if ( (*p) == 100 )
		goto st221;
	goto st0;
st221:
	if ( ++p == pe )
		goto _test_eof221;
case 221:
	if ( (*p) == 45 )
		goto st222;
	goto st0;
st222:
	if ( ++p == pe )
		goto _test_eof222;
case 222:
	if ( (*p) == 115 )
		goto tr246;
	goto st0;
st223:
	if ( ++p == pe )
		goto _test_eof223;
case 223:
	if ( (*p) == 101 )
		goto st224;
	goto st0;
st224:
	if ( ++p == pe )
		goto _test_eof224;
case 224:
	if ( (*p) == 113 )
		goto st225;
	goto st0;
st225:
	if ( ++p == pe )
		goto _test_eof225;
case 225:
	if ( (*p) == 45 )
		goto st226;
	goto st0;
st226:
	if ( ++p == pe )
		goto _test_eof226;
case 226:
	if ( (*p) == 115 )
		goto tr250;
	goto st0;
	}
	_test_eof227: cs = 227; goto _test_eof; 
	_test_eof228: cs = 228; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
	_test_eof139: cs = 139; goto _test_eof; 
	_test_eof140: cs = 140; goto _test_eof; 
	_test_eof141: cs = 141; goto _test_eof; 
	_test_eof142: cs = 142; goto _test_eof; 
	_test_eof143: cs = 143; goto _test_eof; 
	_test_eof144: cs = 144; goto _test_eof; 
	_test_eof145: cs = 145; goto _test_eof; 
	_test_eof146: cs = 146; goto _test_eof; 
	_test_eof147: cs = 147; goto _test_eof; 
	_test_eof148: cs = 148; goto _test_eof; 
	_test_eof149: cs = 149; goto _test_eof; 
	_test_eof150: cs = 150; goto _test_eof; 
	_test_eof151: cs = 151; goto _test_eof; 
	_test_eof152: cs = 152; goto _test_eof; 
	_test_eof153: cs = 153; goto _test_eof; 
	_test_eof154: cs = 154; goto _test_eof; 
	_test_eof155: cs = 155; goto _test_eof; 
	_test_eof156: cs = 156; goto _test_eof; 
	_test_eof157: cs = 157; goto _test_eof; 
	_test_eof158: cs = 158; goto _test_eof; 
	_test_eof159: cs = 159; goto _test_eof; 
	_test_eof160: cs = 160; goto _test_eof; 
	_test_eof161: cs = 161; goto _test_eof; 
	_test_eof162: cs = 162; goto _test_eof; 
	_test_eof163: cs = 163; goto _test_eof; 
	_test_eof164: cs = 164; goto _test_eof; 
	_test_eof165: cs = 165; goto _test_eof; 
	_test_eof166: cs = 166; goto _test_eof; 
	_test_eof167: cs = 167; goto _test_eof; 
	_test_eof168: cs = 168; goto _test_eof; 
	_test_eof169: cs = 169; goto _test_eof; 
	_test_eof170: cs = 170; goto _test_eof; 
	_test_eof171: cs = 171; goto _test_eof; 
	_test_eof172: cs = 172; goto _test_eof; 
	_test_eof173: cs = 173; goto _test_eof; 
	_test_eof174: cs = 174; goto _test_eof; 
	_test_eof175: cs = 175; goto _test_eof; 
	_test_eof176: cs = 176; goto _test_eof; 
	_test_eof177: cs = 177; goto _test_eof; 
	_test_eof178: cs = 178; goto _test_eof; 
	_test_eof179: cs = 179; goto _test_eof; 
	_test_eof180: cs = 180; goto _test_eof; 
	_test_eof181: cs = 181; goto _test_eof; 
	_test_eof182: cs = 182; goto _test_eof; 
	_test_eof183: cs = 183; goto _test_eof; 
	_test_eof184: cs = 184; goto _test_eof; 
	_test_eof185: cs = 185; goto _test_eof; 
	_test_eof186: cs = 186; goto _test_eof; 
	_test_eof187: cs = 187; goto _test_eof; 
	_test_eof188: cs = 188; goto _test_eof; 
	_test_eof189: cs = 189; goto _test_eof; 
	_test_eof190: cs = 190; goto _test_eof; 
	_test_eof191: cs = 191; goto _test_eof; 
	_test_eof192: cs = 192; goto _test_eof; 
	_test_eof193: cs = 193; goto _test_eof; 
	_test_eof194: cs = 194; goto _test_eof; 
	_test_eof195: cs = 195; goto _test_eof; 
	_test_eof196: cs = 196; goto _test_eof; 
	_test_eof197: cs = 197; goto _test_eof; 
	_test_eof198: cs = 198; goto _test_eof; 
	_test_eof199: cs = 199; goto _test_eof; 
	_test_eof200: cs = 200; goto _test_eof; 
	_test_eof201: cs = 201; goto _test_eof; 
	_test_eof202: cs = 202; goto _test_eof; 
	_test_eof203: cs = 203; goto _test_eof; 
	_test_eof204: cs = 204; goto _test_eof; 
	_test_eof205: cs = 205; goto _test_eof; 
	_test_eof206: cs = 206; goto _test_eof; 
	_test_eof207: cs = 207; goto _test_eof; 
	_test_eof208: cs = 208; goto _test_eof; 
	_test_eof209: cs = 209; goto _test_eof; 
	_test_eof210: cs = 210; goto _test_eof; 
	_test_eof211: cs = 211; goto _test_eof; 
	_test_eof212: cs = 212; goto _test_eof; 
	_test_eof213: cs = 213; goto _test_eof; 
	_test_eof214: cs = 214; goto _test_eof; 
	_test_eof215: cs = 215; goto _test_eof; 
	_test_eof216: cs = 216; goto _test_eof; 
	_test_eof217: cs = 217; goto _test_eof; 
	_test_eof218: cs = 218; goto _test_eof; 
	_test_eof219: cs = 219; goto _test_eof; 
	_test_eof220: cs = 220; goto _test_eof; 
	_test_eof221: cs = 221; goto _test_eof; 
	_test_eof222: cs = 222; goto _test_eof; 
	_test_eof223: cs = 223; goto _test_eof; 
	_test_eof224: cs = 224; goto _test_eof; 
	_test_eof225: cs = 225; goto _test_eof; 
	_test_eof226: cs = 226; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 228: goto tr264;
	}
	}

	_out: {}
	}

#line 76 "DataScanner.rl"
                return type;
            }
        private:
            int cs,act;
            int type;
            const char *te,*ts;
    };
