#include <iostream>

#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <errno.h>

using namespace std;

struct regcmd {
	unsigned int cmd;
	unsigned int adr;
	unsigned int dat;
};

int main(int argc, char *argv[])
{
	int fd;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	struct regcmd rc;

	fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (fd == -1) {
		cerr << "host: " << strerror(errno);
		return -1;
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6688);
	inet_aton("127.0.0.1", &addr.sin_addr);

	rc.cmd = 1;
	rc.adr = 0;
	rc.dat = 0x12345678;
	sendto(fd, &rc, sizeof(rc), 0, (struct sockaddr*)&addr, len);

	rc.cmd = 0;
	rc.adr = 0;
	rc.dat = 0x12345678;
	sendto(fd, &rc, sizeof(rc), 0, (struct sockaddr*)&addr, len);

	cout << "read: address: 0x" << hex << rc.adr << ", data: 0x" << hex << rc.dat << endl;

	close(fd);

	return 0;
}
