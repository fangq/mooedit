/*
 * netinet/in.h — minimal MinGW shim.
 *
 * xdgmime/xdgmimecache.c includes <netinet/in.h> just to pick up ntohl()
 * and ntohs() for big-endian cache reads.  MinGW's libc doesn't ship that
 * POSIX header; on Windows the same functions live in <winsock2.h>.
 */
#ifndef MOO_MINGW_NETINET_IN_H
#define MOO_MINGW_NETINET_IN_H

#include <winsock2.h>

#endif /* MOO_MINGW_NETINET_IN_H */
