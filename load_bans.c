/* ---------------------------------------------------------------------------
 * Copyright (c) GOTUNIX Networks
 * Copyright (c) GOTUNIXCODE
 * Copyright (c) Justin Ovens
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ---------------------------------------------------------------------------
 */

#include "services.h"

int	load_bans		();

/////////////////////////////////////////////////////////////////////////////
//

int
load_bans ()
{
	ChanDB	*cs;
	FILE	*bans, *new;
	char	read[512], *ptr[5];

	cs = chandb;
	bans = fopen("bans.db", "r");

	if (!bans)
	{
		new = fopen("bans.db", "a");
		fprintf(new, "; bans dbase\n");
		fclose(new);
		return 0;
	}
	else
	{
		while (fgets(read, 256, bans) != NULL)
		{
			if (read[0] == ';')
			{
				continue;
			}

			ptr[0] = strtok(read, ":");
			ptr[1] = strtok(NULL, ":");
			ptr[2] = strtok(NULL, "\n");

			cs = findChan(ptr[0]);
			if (!cs)
			{
				return 0;
			}
			else
			{
				addBan(ptr[0], ptr[1], ptr[2], cs->bot);
			}
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//


