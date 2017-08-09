/*

The VFS module `disable_chmod_acl` disables mode changes that Samba would
provide after the Kernel propagated default POSIX ACLs.

The implementation is based on `examples/VFS/skel_opaque.c`.

Example config to propagate default ACLs for user and group, explicitly masking
other:

```
[testdata-disable-chmod-acl]
  path                  = /samba/testdata-disable-chmod-acl
  browseable            = yes
  wide links            = yes
  writable              = yes
  create mask           = 0660
  force create mode     = 0660
  directory mask        = 0770
  force directory mode  = 0770
  inherit acls          = no
  inherit permissions   = no
  vfs objects           = disable_chmod_acl
```

*/

#include "../source3/include/includes.h"
#include "lib/util/tevent_ntstatus.h"

static int disable_chmod_acl_chmod_acl(vfs_handle_struct *handle,
				       const char *name, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}

static int disable_chmod_acl_fchmod_acl(vfs_handle_struct *handle,
				        files_struct *fsp, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}

struct vfs_fn_pointers disable_chmod_acl_fns = {
	.chmod_acl_fn = disable_chmod_acl_chmod_acl,
	.fchmod_acl_fn = disable_chmod_acl_fchmod_acl,
};

NTSTATUS vfs_disable_chmod_acl_init(void)
{
	return smb_register_vfs(SMB_VFS_INTERFACE_VERSION, "disable_chmod_acl",
				&disable_chmod_acl_fns);
}
