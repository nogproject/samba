/*
   Unix SMB/CIFS implementation.
   Wrap unix errno around tevent_req
   Copyright (C) Volker Lendecke 2009

     ** NOTE! The following LGPL license applies to the tevent_unix
     ** helper library. This does NOT imply that all of Samba is released
     ** under the LGPL

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../replace/replace.h"
#include "tevent_unix.h"

bool tevent_req_is_unix_error(struct tevent_req *req, int *perrno)
{
	enum tevent_req_state state;
	uint64_t err;

	if (!tevent_req_is_error(req, &state, &err)) {
		return false;
	}
	switch (state) {
	case TEVENT_REQ_TIMED_OUT:
		*perrno = ETIMEDOUT;
		break;
	case TEVENT_REQ_NO_MEMORY:
		*perrno = ENOMEM;
		break;
	case TEVENT_REQ_USER_ERROR:
		*perrno = err;
		break;
	default:
		*perrno = EINVAL;
		break;
	}
	return true;
}

int tevent_req_simple_recv_unix(struct tevent_req *req)
{
	int err = 0;

	/*
	 * Ignore result of tevent_req_is_unix_error, we're only interested in
	 * the status
	 */
	tevent_req_is_unix_error(req, &err);
	tevent_req_received(req);
	return err;
}

bool tevent_req_poll_unix(struct tevent_req *req, struct tevent_context *ev,
			  int *err)
{
	bool ret = tevent_req_poll(req, ev);
	if (!ret) {
		*err = errno;
	}
	return ret;
}
