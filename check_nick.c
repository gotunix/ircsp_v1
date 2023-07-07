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

void	checknick		(void);

///////////////////////////////////////////////////////////////////////////////
//

void
checknick (void)
{
	Nick		*n;
	nickservDB	*ns;

	n = nick;
	ns = nickservdb;

	while (ns)
	{
		//////////////////////////////////////////////////////////////
		// check if temp->nickname is registered.
		//

		n = findNick(ns->nickname);
		if (!n)
		{
			//////////////////////////////////////////////////////
			// temp->nickname is not a registered nickname, 
			// so don't do anything.
			//
		}
		else
		{
			if (!IsNSAuth(ns))
			{
				//////////////////////////////////////////////
				// make sure temp->nickname is not already 
				// authorized.

				if (IsNSKillProt(ns))
				{

					///////////////////////////////////////////////////////
					// temp->nickname has kill protection on, if he does,
					// give him 2 minutes to authorize, and if he don't
					// remove him from the network.
					//

					if ((time(NULL) - n->ConnTime) > 120)
					{ 
						//////////////////////////////////////////////////
						// user has faild to authorize, so remove him/her
						// from the network.
						//
						send_to_sock(s, 
							":%s KILL %s :%s\n",
							config->nnick, ns->nickname,
							"User faild to authorize with NS.");
						delNick(ns->nickname);
					}
					else
					{
						send_to_sock(s, 
							":%s NOTICE %s :%s\n",
							config->nnick, ns->nickname,
							"You're using a registered nickname, please authorize.");
						send_to_sock(s, 
							":%s NOTICE %s :\2/msg %s AUTH %s <password>\n",
							config->nnick, ns->nickname, 
							config->nnick, ns->nickname);
					}
				}
				else
				{
					////////////////////////////////////////////////////////
					// temp->nickname doesn't have kill protection on,
					// so keep sending please auth yourself messages.
					//

					send_to_sock(s, 
						":%s NOTICE %s :%s\n",
						config->nnick, ns->nickname,
						"You're using a registered nickname, please authorize.");
					send_to_sock(s, 
						":%s NOTICE %s :\2/msg %s AUTH %s <password>\n",
						config->nnick, ns->nickname, 
						config->nnick, ns->nickname);
				}
			}
		}
         
		////////////////////////////////////////////////////////////////////
		// move to the next nickname in our nick list.
		//

		ns = ns->next;
	}
}

///////////////////////////////////////////////////////////////////////////////
//


