#define EXP_ETHER_ADDR_LEN		6
#define EXP_ETHER_HDR_LEN		14
#define EXP_ETHER_OCT_LEN		2
#define MAC_ADDRESS_SIZE		17
int mac_address_size = 17;

struct exp_mac_addr{
	char mac_string[18];
	u_int8_t* mac_network;
};

//Returns a random mac address
void random_mac_address(struct exp_mac_addr* mac_struct)
{
	char mac[18];
	memset(mac, '\0', 0);
	sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", (unsigned char)rand(), (unsigned char)rand(), (unsigned char)rand(), (unsigned char)rand(), (unsigned char)rand(), (unsigned char)rand());

	memset(mac_struct->mac_string, '\0', 0);
	strncpy(mac_struct->mac_string, mac, (size_t)MAC_ADDRESS_SIZE);
	mac_struct->mac_network = libnet_hex_aton(mac, &mac_address_size);
}

void mac_address_with_vendor(unsigned const char* vendor, struct exp_mac_addr* mac_struct){
        char mac[18];
        memset(mac, '\0', 0);
        sprintf(mac, "%s:%02x:%02x:%02x", vendor, (unsigned char)rand(), (unsigned char)rand(), (unsigned char)rand());
        memset(mac_struct->mac_string, '\0', 0);

        strncpy(mac_struct->mac_string, mac, sizeof(mac_struct->mac_string));//(size_t)MAC_ADDRESS_SIZE);
        mac_struct->mac_network = libnet_hex_aton(mac, &mac_address_size);
}

void mac_address(struct exp_mac_addr* mac_struct, const char* mac_addr)
{
        char mac[18];
        memset(mac, '\0', 0);
        sprintf(mac, "%s", mac_addr);

        memset(mac_struct->mac_string, '\0', 0);
        strncpy(mac_struct->mac_string, mac, (size_t)MAC_ADDRESS_SIZE);
        mac_struct->mac_network = libnet_hex_aton(mac, &mac_address_size);
}

/*char* MACADDR_to_char(u_int8_t* MACaddress)
{
	char* mac_pointer = (char*)MACaddress;
	char macaddress[18];
	for(int i = 0; i < 6; i++)
		snprintf(macaddress, "%02x", mac_pointer+i);
	return macaddress;
}*/

void printMAC(const char * text, unsigned char hw1, unsigned char hw2, unsigned char hw3, unsigned char hw4, unsigned char hw5, unsigned char hw6)
{
	printf("\nMAC address for [%s] is: %x:%x:%x:%x:%x:%x", text, hw1, hw2, hw3, hw4, hw5, hw6);
	return;
}

void zero_out(void* struct_, size_t siz)
{
	memset(struct_, 0, siz);
}

//finish
struct ethhdr* set_ethernet_addr(unsigned char* source, unsigned char* dest, char* buffer)
{
	struct ethhdr* ether = (struct ethhdr*)buffer;
	return ether;
}

struct ether_hdr
{
	unsigned char	destination_addr[ETHER_ADDR_LEN];
	unsigned char	source_addr[ETHER_ADDR_LEN];
	__be16		eth_protocol;
};

struct ip_hdr
{
	unsigned char ip_version_and_header_length;
	unsigned char ip_tos;
	unsigned short ip_len;
	unsigned short ip_id;
	unsigned short ip_frag_offset;
	unsigned char ip_ttl;
	unsigned char ip_type;
	unsigned short ip_checksum;
	unsigned int ip_src_addr;
	unsigned int ip_dest_addr;
};

struct tcp_hdr
{
	unsigned short tcp_src_port;
	unsigned short tcp_dest_port;
	unsigned int tcp_seq;
	unsigned int tcp_ack;
	unsigned char reserved:4;
	unsigned char tcp_offset:4;
	unsigned char tcp_flags;

	#define TCP_FIN	0x01
	#define TCP_SYN 0x02
	#define TCP_RST 0x04
	#define TCP_PUSH 0x08
	#define TCP_ACK 0x10
	#define TCP_URG 0x20

	unsigned short tcp_window;
	unsigned short tcp_checksum;
	unsigned short tcp_urgent;
};

//Remember to correct len if using a raw socket by multiplying the DWORDS by the correct value
unsigned char* n_all_hex(const u_char* buffer, int len)
{
	int cur = 0;
        unsigned int out_buff_x[16];
        u_char out_buff_c[16];

	unsigned char* out_buff_VODKA = (unsigned char*)malloc(4096);

	printf("\n[PACKET] >> Handling %d byte packet:\n\n------\n\n", len);
        for(int i = 0; i < len; i++)
        {
                if((i % 16) == 1)
                {
                        cur = 0;
                        for(int j = 0; j <= 32; j++)
                        {
                                if(j <= 15)
                                        printf("0x%.2x ", out_buff_x[j]);
                                        if(j == 16)
                                                printf(" | ");
                                else
                                        printf("%c", out_buff_c[j-16]);
                        }
                        printf("\n");
                }
                else
                {
			if(buffer[i] > 32 && buffer[i] < 127)
                        {
                                out_buff_c[cur] = buffer[i];
                                out_buff_x[cur] = buffer[i];
                        }
                        else
                        {
                                out_buff_c[cur] = '.';
                                out_buff_x[cur] = 0;
                        }
                }
                cur++;
        }
	//printf("DATA:\n------\n%s", out_buff_VODKA);
        return out_buff_VODKA;
}

int n_all(unsigned const char* buffer, int length, int modulo)
{
	for(int i = 0; i <  length; i++)
	{
		if((i % modulo) == 1)
			printf("\n");

		if(buffer[i] > 32 && buffer[i] < 127)
			printf("%c", buffer[i]);
		else
			printf(".");
	}
	return 1;
}
