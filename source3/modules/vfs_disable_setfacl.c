/*

The VFS module `disable_setfacl` prevents POSIX ACL changes by pretending that
`sys_acl_set_*` and `sys_acl_delete_*` calls were successful without modifying
the file system.  By itself, it does not prevent all mode changes.  It should
be used together with the VFS module `disable_chmod`.

The implementation is based on `examples/VFS/skel_opaque.c`.

*/

#include "../source3/include/includes.h"
#include "lib/util/tevent_ntstatus.h"

static int disable_setfacl_sys_acl_set_file(vfs_handle_struct *handle,
					    const char *name,
					    SMB_ACL_TYPE_T acltype,
					    SMB_ACL_T theacl)
{
	return 0;
}

static int disable_setfacl_sys_acl_set_fd(vfs_handle_struct *handle,
					  files_struct *fsp,
					  SMB_ACL_T theacl)
{
	return 0;
}

static int disable_setfacl_sys_acl_delete_def_file(vfs_handle_struct *handle,
						   const char *path)
{
	return 0;
}

struct vfs_fn_pointers disable_setfacl_fns = {
	.sys_acl_set_file_fn = disable_setfacl_sys_acl_set_file,
	.sys_acl_set_fd_fn = disable_setfacl_sys_acl_set_fd,
	.sys_acl_delete_def_file_fn = disable_setfacl_sys_acl_delete_def_file,
};

NTSTATUS vfs_disable_setfacl_init(void)
{
	return smb_register_vfs(SMB_VFS_INTERFACE_VERSION, "disable_setfacl",
				&disable_setfacl_fns);
}
