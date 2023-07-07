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

///////////////////////////////////////////////////////////////////////////////
//

int	load_cadmin		();

///////////////////////////////////////////////////////////////////////////////
//

int
load_cadmin ()
{
	FILE	*fp, *new;
	char	read[512], *ptr[6];

	fp = fopen("cadmin.db", "r");
	if (!fp)
	{
		new = fopen("cadmin.db", "a");
		fprintf(new, "; Channel Admin Database\n");
		fclose(new);
		return 0;
	}
	else
	{
		while (fgets(read, 256, fp) != NULL)
		{
			if (read[0] == ';')
			{
				continue;
			}

			ptr[0] = strtok(read, ":");
			ptr[1] = strtok(NULL, ":");
			ptr[2] = strtok(NULL, ":");
			ptr[3] = strtok(NULL, ":");
			ptr[4] = strtok(NULL, "\n");

			addCadmin(ptr[0], ptr[1], ptr[2], atoi(ptr[3]),
				atoi(ptr[4]));
		}
		fclose(fp);
		return 1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//


