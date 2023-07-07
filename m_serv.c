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

int	m_stats			(char *);

//////////////////////////////////////////////////////////////////////////////
//

int
m_stats (buf)
char	*buf;
{
	char	*ptr[5];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[2] = strtok(NULL, " ");

	if (!strcasecmp(ptr[2], "VERSION"))
	{
		send_to_sock(s, 
			"NOTICE %s :IRCSP [\2%s\2]\n",
			ptr[0], VERSION);

		send_to_sock(s, 
			"NOTICE %s :Copyright (C) 1999 Lostworld Development.\n", 
			ptr[0]);

		send_to_sock(s, 
			"NOTICE %s :Written By: Justin Ovens (evilicey)\n", 
			ptr[0]);

		send_to_sock(s, 
			"NOTICE %s :Compiled on: %s [%s] \n",
			ptr[0], __DATE__, __TIME__);

		send_to_sock(s, 
			"NOTICE %s :$Last Source Update$ %s\n",
			ptr[0], DATE);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


