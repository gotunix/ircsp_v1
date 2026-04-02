///////////////////////////////////////////////////////////////////////////////
//		  IRCSP - Internet Realy Chat Services Package
//                  Copyright (C) 2000 Lostworld Development
//          Written By: Justin Ovens [evilicey] [ice95@lostworld.net]
//
//   This program, documentation, and everything included in this
//   package are Copyright (C) 2000 Lostworld Development. You may
//   Download this package from the lostworld site, or via CVS
//   from source forge.
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 1, or (at your option)
//   any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//   The authors of this program are in no way liable for any
//   consequences or damages, suffered by you or anyone else,
//   arising out of the use or inablility to use this program.
//
//   Author Contact information: ice95@lostworld.net
///////////////////////////////////////////////////////////////////////////////


#define E extern

E	char	*token			(char *, int);
E	char	*lrange			(char *, int);
E	int	tokenize		(char *, char);
E	int	numtokens		(char *);
E	char	*strtoupper		(char *);
E	char	*nocolon		(char *);   
E	char    *chop                   (char *);
E	int	match			(const char *, const char *);

/**** socket.c ****/

E	int	send_to_sock		(int socket, const char *fmt, ...);
E	int	conn 			();
E	int	sockread		(int, char *);

/**** link_admin.c ****/

E	Admin	*addAdmin		(char *, int,  char *, int, int, \
	 				 	char *);
E	Admin	*findAdmin		(char *);
E	void	delAdmin		(char *);


/**** link_bans ****/

E	Bans	*addBan			(char *, char *, char *, char *);
E	Bans	*findBan		(char *, char *);
E	void	delBan			(char *, char *);

/**** link_channel.c ****/

E	ChanDB	*addChan		(char *, char *, char *, char *);
E	ChanDB	*findChan		(char *);
E	void	delChan			(char *);

/**** link_gline.c ****/

E	struct	aGline	*addGline	(char *, time_t, time_t, char *);
E	struct	aGline	*findGline	(char *);
E	void		rem_gline	(char *);

/**** link_cadmin.c ****/

E	Cadmin	*addCadmin		(char *, char *, char *, int, int);
E	Cadmin	*findCadmin		(char *, char *);
E	Cadmin	*findCadmin_nick	(char *);
E	void	delCadmin		(char *, char *);

/**** link_nick.c ****/

E	nickservDB	*NSAddNick	(char *, char *, int, int);
E	nickservDB	*NSFindNick	(char *);
E	void		NSdelNick	(char *);

/**** link_nickname.c ****/

E	Nick	*addNick		(char *, char *, char *, char *, \
						int, time_t);
E	Nick	*findNick		(char *);
E	Nick	*findNickbyHost		(char *);
E	void	delNick			(char *);

/**** link_hosts.c ****/

E	Hosts	*addHost		(char *);
E	Hosts	*findHost		(char *);
E	void	delHost			(char *);

/**** link_clones.c ****/

E	Clones	*addClone		(char *, char *, char *);
E	Clones	*findClone		(char *);
E	Clones	*findClonebyUser	(char *);
E	void	delClone		(char *);

/**** link_suspchan.c ****/

E	SuspChan	*addSChan	(char *, char *);
E	void		delSChan	(char *);

/**** boot.c ****/

E	int	boot_copyright		();
E	int	boot_help		();

/**** chanserv.c ****/

E	int	do_chanserv		(char *, char *, char *);

/**** check_clones.c ****/

E	void	checkclones		(void);

/**** check_chan.c ****/

E	void	checkchan		(void);

/**** check_gline.c ****/

E	void	checkgline		(void);

/**** check_nick.c ****/

E	void	checknick		(void);

/**** helpserv.c ****/

E	int	do_helpserv		(char *, char *, char *);
E	int	do_hs_help		(char *);


/**** load_admin.c ****/

E	int	load_admin		();

/**** load_bans.c ****/

E	int	load_bans		();

/**** load_channels.c ****/

E	int	load_channel		();

/**** load_config.c ****/

E	int	load_config		();

/**** load_gline.c ****/

E	int	load_gline		();

/**** load_nick.c ****/

E	int	load_nick		();

/**** load_suspchan.c ****/

E	int	load_suspchan		();

/**** load_cadmin.c ****/

E	int	load_cadmin		();

/**** m_serv.c ****/

E	int	m_stats			(char *);

/**** memoserv.c ****/

E	int	do_memoserv		(char *, char *, char *);

/**** nickserv.c ****/

E	int	do_nickserv		(char *, char *, char *);
E	int	do_ns_help		(char *);
E	int	do_ns_auth		(char *);
E	int	do_ns_reg		(char *);
E	int	do_ns_drop		(char *);

/**** parse.c ****/

E	int	parse			(char *);

/**** parse_cmode.c ****/

E	int	parse_cmode		(char *, char *, char *);

/**** parse_nickname.c ****/

E	int	parse_nickname		(char *);

/**** parse_umode.c ****/

E	int	parse_umode		(char *, char *);

/**** parse_kill.c ****/

E	int	parse_kill		(char *, char *);


/**** save_admin.c ****/

E	int	save_admin		();

/**** save_cadmin.c ****/

E	int	save_cadmin		();

/**** save_bans.c ****/

E	int	save_bans		();

/**** save_channel.c ****/

E	int	save_channel		();

/**** save_gline.c ****/

E	int	save_gline		();

/**** save_nsdb.c ****/

E	int	save_nsdb		();

/**** uworld.c ****/

E	int	do_uworld		(char *, char *, char *);
E	int	do_help			(char *);
E	int	do_auth			(char *);
E	int	do_gline		(char *);
E	int	do_mode			(char *);
E	int	do_kick			(char *);
E	int	do_kill			(char *);
E	int	do_masskill		(char *);
E	int	do_clearmode		(char *);
E	int	do_uptime		(char *);
E	int	num_nuk			(char *);
E	int	do_join			(char *);
E	int	do_part			(char *);
E	int	do_verify		(char *);
E	int	do_operlist		(char *);
E	int	do_map			(char *);
E	int	do_invite		(char *);
E	int	do_whois		(char *);
E	int	do_access		(char *);
E	int	do_mkpasswd		(char *);
E	int	do_count		(char *);
E	int	do_opermsg		(char *);
E	int	do_jupe			(char *);
E	int	do_remjupe		(char *);
E	int	do_rehash		(char *);
E	int	do_save			(char *);
E	int	do_collide		(char *);
E	int	do_suspend		(char *);
E	int	do_remsuspend		(char *);
E	int	do_adduser		(char *);
E	int	do_moduser		(char *);
E	int	do_remuser		(char *);
E	int	do_say			(char *);
E	int	do_action		(char *);
E	int	do_raw			(char *);

/**** wbot.c ****/

E	int	do_wbot			(char *, char *, char *);
E	int	do_w_auth		(char *);
E	int	do_w_help		(char *);

/**** xbot.c ****/

E	int	do_xbot			(char *, char *, char *);

/**** handler.c ****/

E	int	Signal_Handler		();

/**** signals.c ****/

E	void	SignalHUP		(int);
E	void	SignalSEGV		(int);

/**** rehash_config.c ****/

E	int	rehash_config		();

/**** rehash_admin.c ****/

E	int	rehash_admin		();

/**** rehash_bans.c ****/

E	int	rehash_bans		();

/**** rehash_cadmin.c ****/

E	int	rehash_cadmin		();

/**** rehash_gline.c ****/

E	int	rehash_gline		();

/**** rehash_nick.c ****/

E	int	rehash_nick		();

/**** rehash_suspchan.c ****/

E	int	rehash_suspchan		();

/**** rehash_channel.c ****/

E	int	rehash_channel		();

