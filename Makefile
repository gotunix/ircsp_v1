# Generated automatically from Makefile.in by configure.
# Generated automatically from Makefile.in by configure.
# Generated automatically from Makefile.in by configure.
# Generated automatically from Makefile.in by configure.
# Generated automatically from Makefile.in by configure.
PROGRAM=services
#CFLAGS=-g -O2 -pipe -Wall -fomit-frame-pointer -fno-strength-reduce -m486
CFLAGS=-g -O2 -pipe -Wall
LIBS=-lcrypt
CC=gcc
OBJS=\
	boot.o chanserv.o check_chan.o check_clones.o check_gline.o	\
	check_nick.o handler.o helpserv.o link_admin.o link_bans.o	\
	link_cadmin.o link_channel.o link_clones.o link_gline.o		\
	link_hosts.o link_jupe.o link_nick.o link_nickname.o  		\
	link_njupe.o link_suspchan.o load_admin.o load_bans.o 		\
	load_cadmin.o load_channels.o load_config.o load_gline.o	\
	load_jupe.o load_nick.o load_njupe.o load_suspchan.o m_serv.o	\
	main.o match.o memoserv.o nickserv.o parse.o parse_cmode.o	\
	parse_kill.o parse_umode.o rehash_admin.o rehash_bans.o		\
	rehash_cadmin.o rehash_channel.o rehash_config.o rehash_gline.o	\
	rehash_jupe.o rehash_nick.o rehash_njupe.o rehash_suspchan.o 	\
	save_admin.o save_bans.o save_cadmin.o save_channel.o 		\
	save_gline.o save_jupe.o save_njupe.o save_nsdb.o signals.o 	\
	socket.o string.o uworld.o wbot.o

ALL:
	@clear
	@make info
	@echo "Begining Compile..."
	@make ircsp
	@echo "And that, is that..."
	@make info


info:
	@echo	"		IRCSP Version 5.1.pre3"
	@echo	"     COPYRIGHT (C) 2000 Lostworld Development"
	@echo	"	Written by: Justin Ovens [evilicey]"
	@echo	""
	@echo	""

ircsp:	${OBJS}
	${CC} -o $@ ${OBJS} ${LIBS}

#${PROGRAM}: ${OBJS}
#	${CC} -o $@ ${OBJS} ${LIBS}

clean:
	@rm *.o
	@rm ircsp
