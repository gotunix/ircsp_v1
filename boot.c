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


#include "services.h"

int	boot_copyright		();
int	boot_help		();


//////////////////////////////////////////////////////////////////////////////
// 

int
boot_copyright ()
{
	FILE		*fp;
	char		read[512];

	fp = fopen("COPYRIGHT", "r");
	if (!fp)
	{
		printf("COPYRIGHT file missing. contact the author.\n");
		exit(1);
	}
	else
	{
		while (fgets(read, 256, fp) != NULL)
		{
			printf("%s", read); 
		}
		exit(1);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//

int
boot_help ()
{
	printf("IRCSP Version %s\n", VERSION);
	printf("Copyright (C) 2000 Lostworld Development\n");
	printf("Written By: Justin Ovens (evilicey)\n");

	printf("\n\n");

	printf("----------------------------------------\n");
	printf("   -h  Displays this\n");
	printf("   -C  Displays Copyright file\n");
	printf("----------------------------------------\n");

	printf("End of help\n");
	printf("\n\nMore to come.\n\n");

	exit(1);
}

///////////////////////////////////////////////////////////////////////////////
//

