#include <stdio.h>

#include <nvscibuf.h>

#define ARRAY_LENGTH(a) (sizeof a / sizeof a[0])

FILE *dbgout;
NvSciBufModule buf_module;

NvSciError create_attr_list(void)
{
	NvSciError rc;

	NvSciBufType buf_type[2] = {NvSciBufType_RawBuffer, NvSciBufType_Image};
	NvSciBufAttrKeyValuePair kvp[] = {
		{NvSciBufGeneralAttrKey_Types, &buf_type, sizeof buf_type},
	};

	NvSciBufAttrList attrs = NULL;
	rc = NvSciBufAttrListCreate(buf_module, &attrs);
	if (rc != NvSciError_Success) {
		fprintf(stderr, "%s: NvSciBufAttrListCreate: erro:%x\n",
			__func__, rc);
		return rc;
	}

	rc = NvSciBufAttrListSetAttrs(attrs, kvp, ARRAY_LENGTH(kvp));
	if (rc != NvSciError_Success) {
		fprintf(stderr, "%s: NvSciBufAttrListSetAttrs: erro:%x\n",
			__func__, rc);
		return rc;
	}

	extern void dump_attr_list(NvSciBufModule, NvSciBufAttrList);
	dump_attr_list(buf_module, attrs);

	return NvSciError_Success;
}

int
main(int ac, char **av)
{
	NvSciError rc;

	dbgout = stderr;

	rc = NvSciBufModuleOpen(&buf_module);
	if (rc != NvSciError_Success) {
		fprintf(stderr, "%s: NvSciBufAttrListSetAttrs: erro:%x\n",
			av[0], rc);
		return 1;
	}

	rc = create_attr_list();
	if (rc != NvSciError_Success)
		return 1;

	return 0;
}
