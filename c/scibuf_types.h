/**
 * @defgroup nvscibuf_blanket_statements NvSciBuf blanket statements.
 * Generic statements applicable for NvSciBuf interfaces.
 * @ingroup nvsci_buf
 * @{
 */

/**
 * \page nvscibuf_page_blanket_statements NvSciBuf blanket statements
 * \section nvscibuf_in_params Input parameters
 * - NvSciBufModule passed as input parameter to an API is valid input if it is
 * returned from a successful call to NvSciBufModuleOpen() and has not yet been
 * deallocated using NvSciBufModuleClose().
 * - NvSciIpcEndpoint passed as input parameter to an API is valid if it is
 * obtained from successful call to NvSciIpcOpenEndpoint() and has not yet been
 * freed using NvSciIpcCloseEndpointSafe().
 * - NvSciBufObj is valid if it is obtained from a successful call to
 * NvSciBufObjAlloc() or if it is obtained from a successful call to
 * NvSciBufAttrListReconcileAndObjAlloc() or if it is obtained from a
 * successful call to NvSciBufObjIpcImport() or if it is obtained from a
 * successful call to NvSciBufObjDup() or if it is obtained from a successful
 * call to NvSciBufObjDupWithReducePerm() and has not been deallocated
 * using NvSciBufObjFree().
 * - Unreconciled NvSciBufAttrList is valid if it is obtained from successful
 * call to NvSciBufAttrListCreate() or if it is obtained from successful call to
 * NvSciBufAttrListClone() where input to NvSciBufAttrListClone() is valid
 * unreconciled NvSciBufAttrList or if it is obtained from successful call to
 * NvSciBufAttrListIpcImportUnreconciled() and has not been deallocated using
 * NvSciBufAttrListFree().
 * - Reconciled NvSciBufAttrList is valid if it is obtained from successful call
 * to NvSciBufAttrListReconcile() or if it is obtained from successful call to
 * NvSciBufAttrListClone() where input to NvSciBufAttrListClone() is valid
 * reconciled NvSciBufAttrList or if it is obtained from successful call to
 * NvSciBufAttrListIpcImportReconciled() and has not been deallocated using
 * NvSciBufAttrListFree().
 * - If the valid range for the input parameter is not explicitly mentioned in
 * the API specification or in the blanket statements then it is considered that
 * the input parameter takes any value from the entire range corresponding to
 * its datatype as the valid value. Please note that this also applies to the
 * members of a structure if the structure is taken as an input parameter.
 * - NvSciBufModule is not sharable accross processes. User must create a new
 * NvSciBufModule using NvSciBufModuleOpen() in every process.
 *
 * \section nvscibuf_out_params Output parameters
 * - In general, output parameters are passed by reference through pointers.
 * Also, since a null pointer cannot be used to convey an output parameter, API
 * functions typically return an error code if a null pointer is supplied for a
 * required output parameter unless otherwise stated explicitly. Output
 * parameter is valid only if error code returned by an API is
 * NvSciError_Success unless otherwise stated explicitly.
 *
 * \section nvscibuf_concurrency Concurrency
 * - Every individual function can be called concurrently with itself without
 * any side-effects unless otherwise stated explicitly in the interface
 * specifications.
 * - The conditions for combinations of functions that cannot be called
 * concurrently or calling them concurrently leads to side effects are
 * explicitly stated in the interface specifications.
 */

/**
 * @}
 */

/**
 * @defgroup nvsci_buf Buffer Allocation APIs
 *
 * The NvSciBuf library contains the APIs for applications to allocate
 * and exchange buffers in memory.
 *
 * @ingroup nvsci_group_stream
 * @{
 */
/**
 * @defgroup nvscibuf_datatype NvSciBuf Datatype Definitions
 * Contains a list of all NvSciBuf datatypes.
 * @{
 */

/**
 * @brief Enum definitions of NvSciBuf datatypes.
 *
 * @implements{17824095}
 */
typedef enum {
    /** Reserved for General keys.
     * Shouldn't be used as valid value for  NvSciBufGeneralAttrKey_Types.
     */
    NvSciBufType_General = 0U,
    NvSciBufType_RawBuffer = 1U,
    NvSciBufType_Image = 2U,
    NvSciBufType_Tensor = 3U,
    NvSciBufType_Array = 4U,
    NvSciBufType_Pyramid = 5U,
    NvSciBufType_MaxValid = 6U,
    NvSciBufType_UpperBound = 6U,
} NvSciBufType;

/**
 * @}
 */

/**
 * @defgroup nvscibuf_constants NvSciBuf Global Constants
 * Definitions of all NvSciBuf Global Constants/Macros
 *
 * @{
 */
/**
 * @brief NvSciBuf API Major version number.
 *
 * @implements{18840105}
 */
static const uint32_t NvSciBufMajorVersion = 2U;

/**
 * @brief NvSciBuf API Minor version number.
 *
 * @implements{18840108}
 */
static const uint32_t NvSciBufMinorVersion = 10U;

#if defined(__cplusplus)

/**
 * @brief Maximum number of dimensions supported by tensor datatype.
 */
static const int NV_SCI_BUF_TENSOR_MAX_DIMS = 8;

/**
 * @brief Maximum number of planes supported by image datatype.
 */
static const int NV_SCI_BUF_IMAGE_MAX_PLANES = 3;

/**
 * @brief Maximum number of levels supported by pyramid datatype.
 */
static const int NV_SCI_BUF_PYRAMID_MAX_LEVELS = 10;

/**
 * @brief Indicates the size of export descriptor.
 */
static const int NVSCIBUF_EXPORT_DESC_SIZE = 32;

/**
 * @brief Maxium number of peer info supported.
 */
static const uint32_t NV_SCI_BUF_PEER_INFO_MAX_NUMBER = 128U;

/**
 * @brief Self SOC ID value if the late peer is from same SoC.
 */
static const uint32_t NV_SCI_BUF_PEER_INFO_SELF_SOCID = 0xFFFFFFFFu;

/**
 * @brief Self VM ID value if the late peer is from same VM.
 */
static const uint32_t NV_SCI_BUF_PEER_INFO_SELF_VMID = 0xFFFFFFFFu;

/**
 * @brief Maximum number of HW Engines supported
 */
static const int NV_SCI_BUF_PEER_HW_ENGINE_MAX_NUMBER = 128U;

/**
 * Maximum number of GPUs that can share the NvSciBufObj.
 * @implements{}
 */
static const uint32_t NV_SCI_BUF_MAX_GPUS = 16u;

/**
 * @brief Indicates number of bits used for defining an attribute key.
 * Note: Maximum 16K attribute Keys per datatype.
 */
static const int NV_SCI_BUF_ATTRKEY_BIT_COUNT = 16;

/**
 * @brief Indicates number of bits used for defining an datatype of a key.
 * Note: Maximum 1K datatypes.
 */
static const int NV_SCI_BUF_DATATYPE_BIT_COUNT = 10;

/**
 * @brief Indicates the attribute key is a public key type.
 */
static const int NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC = 0;

/*
 * @brief Global constant to specify the start-bit of attribute Keytype.
 */
static const int NV_SCI_BUF_KEYTYPE_BIT_START =
        (NV_SCI_BUF_DATATYPE_BIT_COUNT + NV_SCI_BUF_ATTRKEY_BIT_COUNT);

/**
 * @brief Indicates starting value of General attribute keys.
 */
static const int NV_SCI_BUF_GENERAL_ATTR_KEY_START =
           (NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) |
           (NvSciBufType_General << NV_SCI_BUF_ATTRKEY_BIT_COUNT);

/**
 * @brief Indicates the start of Raw-buffer Datatype keys.
 */
static const int NV_SCI_BUF_RAW_BUF_ATTR_KEY_START =
           (NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) |
           (NvSciBufType_RawBuffer << NV_SCI_BUF_ATTRKEY_BIT_COUNT);

/**
 * @brief Indicates the start of Image Datatype keys.
 */
static const int NV_SCI_BUF_IMAGE_ATTR_KEY_START =
           (NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) |
           (NvSciBufType_Image << NV_SCI_BUF_ATTRKEY_BIT_COUNT);

/**
 * @brief Indicates the start of ImagePyramid Datatype keys.
 */
static const int NV_SCI_BUF_PYRAMID_ATTR_KEY_START =
           (NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) |
           (NvSciBufType_Pyramid << NV_SCI_BUF_ATTRKEY_BIT_COUNT);

/**
 * @brief Indicates the start of NvSciBuf Array Datatype keys.
 */
static const int NV_SCI_BUF_ARRAY_ATTR_KEY_START =
           (NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) |
           (NvSciBufType_Array << NV_SCI_BUF_ATTRKEY_BIT_COUNT);

/**
 * @brief Indicates the start of Tensor Datatype keys.
 */
static const int NV_SCI_BUF_TENSOR_ATTR_KEY_START =
           (NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) |
           (NvSciBufType_Tensor << NV_SCI_BUF_ATTRKEY_BIT_COUNT);

#else

/**
 * @brief Maximum number of dimensions supported by NvSciBufType_Tensor.
 *
 * @implements{18840096}
 */
#define NV_SCI_BUF_TENSOR_MAX_DIMS  8u

/**
 * @brief Maximum number of planes supported by NvSciBufType_Image.
 *
 * @implements{18840099}
 */
#define NV_SCI_BUF_IMAGE_MAX_PLANES 3u

/**
 * @brief Maximum number of levels supported by NvSciBufType_Pyramid.
 */
#define NV_SCI_BUF_PYRAMID_MAX_LEVELS 10u

/**
 * @brief Indicates the size of export descriptor.
 */
#define NVSCIBUF_EXPORT_DESC_SIZE   32u

/**
 * @brief Maxium number of peer info supported.
 */
#define NV_SCI_BUF_PEER_INFO_MAX_NUMBER 128u

/**
 * @brief Self SOC ID value if the late peer is from same SoC.
 */
#define NV_SCI_BUF_PEER_INFO_SELF_SOCID 0xFFFFFFFFu

/**
 * @brief Self VM ID value if the late peer is from same VM.
 */
#define NV_SCI_BUF_PEER_INFO_SELF_VMID 0xFFFFFFFFu

/**
 * @brief Global Constant to define maximum number of NvSciBufPeerHwEngine
 * supported.
 */
#define NV_SCI_BUF_PEER_HW_ENGINE_MAX_NUMBER  128U

/**
 * Maximum number of GPUs that can share the NvSciBufObj.
 * @implements{}
 */
#define NV_SCI_BUF_MAX_GPUS 16

/**
 * @brief Global constant to indicate number of bits used for
 * defining an attribute key. Note: Maximum 16K attribute keys
 * per NvSciBufType.
 */
#define NV_SCI_BUF_ATTRKEY_BIT_COUNT  16u

/**
 * @brief Global constant to indicate number of bits used for
 * defining NvSciBufType of an attribute key. Note: Maximum 1K
 * NvSciBufType(s).
 */
#define NV_SCI_BUF_DATATYPE_BIT_COUNT  10u

/**
 * @brief Global constant to indicate the attribute key type is public.
 */
#define NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC 0u

/**
 * @brief Global constant to specify the start-bit of attribute key type.
 */
#define NV_SCI_BUF_KEYTYPE_BIT_START \
        (NV_SCI_BUF_DATATYPE_BIT_COUNT + NV_SCI_BUF_ATTRKEY_BIT_COUNT)

/**
 * @brief Indicates starting value of NvSciBufAttrKey for NvSciBufType_General.
 */
#define NV_SCI_BUF_GENERAL_ATTR_KEY_START \
        ((NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) | \
        (NvSciBufType_General << NV_SCI_BUF_ATTRKEY_BIT_COUNT))

/**
 * @brief Indicates starting value of NvSciBufAttrKey for NvSciBufType_RawBuffer.
 */
#define NV_SCI_BUF_RAW_BUF_ATTR_KEY_START \
          ((NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) | \
          (NvSciBufType_RawBuffer << NV_SCI_BUF_ATTRKEY_BIT_COUNT))

/**
 * @brief Indicates the starting value of NvSciBufAttrKey for NvSciBufType_Image.
 */
#define NV_SCI_BUF_IMAGE_ATTR_KEY_START \
          ((NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) | \
          (NvSciBufType_Image << NV_SCI_BUF_ATTRKEY_BIT_COUNT))

/**
 * @brief Indicates the starting value of NvSciBufAttrKey for NvSciBufType_Pyramid.
 */
#define NV_SCI_BUF_PYRAMID_ATTR_KEY_START \
          ((NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) | \
          (NvSciBufType_Pyramid << NV_SCI_BUF_ATTRKEY_BIT_COUNT))

/**
 * @brief Indicates the starting value of NvSciBufAttrKey for NvSciBufType_Array.
 */
#define NV_SCI_BUF_ARRAY_ATTR_KEY_START \
          ((NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) | \
          (NvSciBufType_Array << NV_SCI_BUF_ATTRKEY_BIT_COUNT))

/**
 * @brief Indicates the starting value of NvSciBufAttrKey for NvSciBufType_Tensor.
 */
#define NV_SCI_BUF_TENSOR_ATTR_KEY_START \
          ((NV_SCI_BUF_ATTR_KEY_TYPE_PUBLIC << NV_SCI_BUF_KEYTYPE_BIT_START) | \
          (NvSciBufType_Tensor << NV_SCI_BUF_ATTRKEY_BIT_COUNT))

#endif

/**
 * @}
 */

/**
 * @defgroup nvscibuf_attr_key NvSciBuf Enumerations for Attribute Keys
 * List of all NvSciBuf enumerations for attribute keys.
 * @{
 */

/**
 * @brief Describes the NvSciBuf public attribute keys holding corresponding
 * values specifying buffer constraints.
 * The accessibility property of an attribute refers to whether the value of an
 * attribute is accessible in an NvSciBufAttrList. Input attribute keys specify
 * desired buffer constraints from client and can be set/retrieved by client
 * to/from unreconciled NvSciBufAttrList using
 * NvSciBufAttrListSetAttrs()/NvSciBufAttrListGetAttrs() respectively.
 * Output attribute keys specify actual buffer constraints computed by NvSciBuf
 * if reconciliation succeeds. Output attributes can be retrieved from
 * reconciled NvSciBufAttrList using NvSciBufAttrListGetAttrs().
 * The presence property of an attribute refers to whether the value of an
 * attribute having accessibility as input needs to be present in at least one
 * of the unreconciled attribute lists for reconciliation.
 * The presence property of an attribute can have one of the three values:
 * Mandatory/Optional/Conditional.
 * Mandatory implies that it is mandatory that the value of an attribute be set
 * in at least one of the unreconciled NvSciBufAttrLists involved in
 * reconciliation. Failing to set mandatory input attribute in at least one of
 * the input unreconciled NvSciBufAttrLists results in reconciliation failure.
 * Optional implies that it is not mandatory that value of an attribute be set
 * in at least of the unreconciled NvSciBufAttrLists involved in reconciliation.
 * If the optional input attribute is not set in any of the input unreconciled
 * NvSciBufAttrLists, NvSciBuf uses default value of such attribute to
 * calculate/reconcile output attributes dependent on such input attribute.
 * Conditional implies that the presence of an attribute is mandatory if
 * condition associated with its presence is satisfied, otherwise its optional.
 *
 * @implements{17824098}
 */
typedef enum {
    /**
     * Specifies the lower bound value to check for a valid NvSciBuf attribute
     * key type.
     */
    NvSciBufAttrKey_LowerBound =         NV_SCI_BUF_GENERAL_ATTR_KEY_START,

    /** An array of all types that the buffer is expected to have. For each type
     * the buffer has, the associated attributes are valid. In order to set
     * @a NvSciBufAttrKeys corresponding to the NvSciBufType, NvSciBufType must
     * be set first using this key.
     * NOTE: A single buffer may have multiple types. For example, a buffer may
     * simultaneously be a NvSciBufType_Image (for integration with NvMedia), a
     * NvSciBufType_Tensor (for integration with TensorRT or NvMedia), and a
     * NvSciBufType_RawBuffer (for integration with CUDA kernels that will
     * directly access it).
     *
     * During reconciliation, if all the NvSciBufTypes
     * specified by all the unreconciled NvSciBufAttrLists are same, this
     * key outputs the specified NvSciBufType. If all NvSciBufTypes are
     * not same, reconciliation succeeds only if the set of NvSciBufTypes
     * contains NvSciBufType_Image and NvSciBufType_Tensor only otherwise
     * reconciliation fails.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if value of this
     * attribute set in any of the input unreconciled NvSciBufAttrList(s) is
     * not present in the set of values of this attribute in the provided
     * reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @ref NvSciBufType[]
     *
     * valid input value: All values defined by NvSciBufType for safety build
     * such that NvSciBufType_General < value < NvSciBufType_MaxValid
     */
    NvSciBufGeneralAttrKey_Types,

    /** Specifies if CPU access is required for the buffer. If this attribute is
     * set to @c true, then the CPU will be able to obtain a pointer to the
     * buffer from NvSciBufObjGetConstCpuPtr() if at least read permissions are
     * granted or from NvSciBufObjGetCpuPtr() if read/write permissions are
     * granted.
     *
     * During reconciliation, reconciler sets value of this key to true in the
     * reconciled NvSciBufAttrList if any of the unreconciled
     * NvSciBufAttrList(s) involved in reconciliation that is owned by the
     * reconciler has this key set to true, otherwise it is set to false in
     * reconciled NvSciBufAttrList.
     *
     * When importing the reconciled NvSciBufAttrList, for every peer owning the
     * unreconciled NvSciBufAttrList(s) involved in reconciliation, if any of
     * the unreconciled NvSciBufAttrList(s) owned by the peer set the key to
     * true then value of this key is true in the reconciled NvSciBufAttrList
     * imported by the peer otherwise its false.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if value of this
     * attribute set in any of the unreconciled NvSciBufAttrList(s) belonging
     * to NvSciIpc channel owner is true and value of the same attribute in
     * reconciled NvSciBufAttrList is false.
     *
     * Accessibility: Input/Output attribute
     * Presence: Optional
     *
     * Value: @c bool
     */
    NvSciBufGeneralAttrKey_NeedCpuAccess,

    /** Specifies buffer access permissions.
     * If reconciliation succeeds, granted buffer permissions are reflected in
     * NvSciBufGeneralAttrKey_ActualPerm. If
     * NvSciBufGeneralAttrKey_NeedCpuAccess is true and write permission
     * are granted, then NvSciBufObjGetCpuPtr() can be used to obtain a
     * non-const pointer to the buffer.
     * NOTE: Whether this key is present in reconciled attribute lists is
     * unspecified, as is its value if it is present.
     *
     * Accessibility: Input attribute
     * Presence: Optional
     *
     * Value: @ref NvSciBufAttrValAccessPerm
     *
     * valid input value: NvSciBufAccessPerm_Readonly or
     * NvSciBufAccessPerm_ReadWrite
     */
    NvSciBufGeneralAttrKey_RequiredPerm,

    /** Specifies whether to enable/disable CPU caching.
     * If set to @c true:
     *
     * The CPU must perform write-back caching of the buffer to the greatest
     * extent possible considering all the CPUs that are sharing the buffer.
     *  Coherency is guaranteed with:
     *         - Other CPU accessors.
     *         - All I/O-Coherent accessors that do not have CPU-invisible
     *           caches.
     *
     * If set to @c false:
     *
     * The CPU must not access the caches at all on read or write accesses
     * to the buffer from applications.
     *  Coherency is guaranteed with:
     *         - Other CPU accessors.
     *         - All I/O accessors (whether I/O-coherent or not) that do not
     *              have CPU-invisible caches.
     *
     * During reconciliation, this key is set to true in reconciled
     * NvSciBufAttrList if any of the unreconciled NvSciBufAttrList owned by any
     * peer set it to true, otherwise it is set to false.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if value of this
     * attribute set in any of the unreconciled NvSciBufAttrList(s) is true and
     * value of the same attribute in reconciled NvSciBufAttrList is false.
     *
     * Accessibility: Input/Output attribute
     * Presence: Optional
     *
     * Value: @c bool
     */
    NvSciBufGeneralAttrKey_EnableCpuCache,

    /** GpuIDs of the GPUs in the system that will access the buffer.
     * In a multi GPU System, if multiple GPUs are supposed to access
     * the buffer, then provide the GPU IDs of all the GPUs that
     * need to access the buffer. The GPU which is not specified in the
     * list of GPUIDs may not be able to access the buffer.
     *
     * During reconciliation, the value of this attribute in reconciled
     * NvSciBufAttrList is equivalent to the aggregate of all the values
     * specified by all the unreconciled NvSciBufAttrLists involved in
     * reconciliation that have this attribute set. The value of this attribute
     * is set to implementation chosen default value if none of the unreconciled
     * NvSciBufAttrLists specify this attribute. Note that the default value
     * chosen by the implementation must be an invalid NvSciRmGpuId value.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if value of this
     * attribute set in any of the input unreconciled NvSciBufAttrList(s) is
     * not present in the set of values of this attribute in the provided
     * reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Optional
     *
     * Value: @ref NvSciRmGpuId[]
     *
     * valid input value: Valid NvSciRmGpuId of the GPU(s) present in the
     * system.
     */
    NvSciBufGeneralAttrKey_GpuId,

    /** Indicates whether the CPU is required to flush before reads and
     * after writes. This can be accomplished using
     * NvSciBufObjFlushCpuCacheRange(), or (if the application prefers) with
     * OS-specific flushing functions. It is set to true in reconciled
     * NvSciBufAttrList if both NvSciBufGeneralAttrKey_EnableCpuCache and
     * NvSciBufGeneralAttrKey_NeedCpuAccess are requested by setting them
     * to true in any of the unreconciled NvSciBufAttrList(s) from which
     * reconciled NvSciBufAttrList is obtained and any of the ISO engines would
     * operate on the buffer.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if value of this
     * attribute reconciled from the input unreconciled NvSciBufAttrList(s) is
     * true and value of the same attribute in the provided reconciled
     * NvSciBufAttrList is false.
     *
     * Accessibility: Output attribute
     *
     * Value: @c bool
     */
    NvSciBufGeneralAttrKey_CpuNeedSwCacheCoherency,

    /** Specifies the buffer access permissions to the NvSciBufObj.
     * This key is only valid in reconciled NvSciBufAttrList
     * and undefined in unreconciled NvSciBufAttrList.
     *
     * During reconciliation, this attribute is set to the maximum value of the
     * requested permission set in NvSciBufGeneralAttrKey_RequiredPerm of all
     * the unreconciled NvSciBufAttrLists are involved in the reconciliation.
     * This attribute is set to default value of NvSciBufAccessPerm_Readonly if
     * none of the unreconciled NvSciBufAttrLists specify value of the
     * NvSciBufGeneralAttrKey_RequiredPerm attribute.
     *
     * If NvSciBufObj is obtained by calling NvSciBufObjAlloc(),
     * NvSciBufGeneralAttrKey_ActualPerm is set to NvSciBufAccessPerm_ReadWrite
     * in the reconciled NvSciBufAttrList corresponding to it since allocated
     * NvSciBufObj gets read-write permissions by default.
     *
     * For any peer importing the reconciled NvSciBufAttrList, this key is set
     * to maximum value of the requested permission set in
     * NvSciBufGeneralAttrKey_RequiredPerm of all the unreconciled
     * NvSciBufAttrLists that were exported by the peer for reconciliation.
     * The key is set by the reconciler when exporting the reconciled
     * NvSciBufAttrList.
     *
     * For any peer importing the NvSciBufObj, this key is set in the reconciled
     * NvSciBufAttrList to the permissions associated with
     * NvSciBufObjIpcExportDescriptor.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if value of this
     * attribute reconciled from the input unreconciled NvSciBufAttrList(s) is
     * greater than the value of the same attribute in the provided reconciled
     * NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     *
     * Value: NvSciBufAttrValAccessPerm
     */
    NvSciBufGeneralAttrKey_ActualPerm,

    /** GPU ID of dGPU from which vidmem allocation should come when multiple
     * GPUs are sharing buffer. This key should be empty if multiple GPUs
     * access shared buffer from sysmem.
     *
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match. This attribute is set to implementation chosen default
     * value if none of the unreconciled NvSciBufAttrLists involved in
     * reconciliation specify this attribute. Note that the default value
     * chosen by the implementation must be an invalid NvSciRmGpuId value.
     *
     * Accessibility: Input/Output attribute
     * Presence: Optional
     *
     * Value: NvSciRmGpuId
     *
     * valid input value: Valid NvSciRmGpuId of the dGPU present in the system.
     */
    NvSciBufGeneralAttrKey_VidMem_GpuId,

    /**
     * An array of NvSciBufAttrValGpuCache[] specifying GPU cacheability
     * requirements.
     *
     * Currently, NvSciBuf supports cacheability control for single iGPU and
     * thus if user decides to request cacheability control via this attribute
     * then an array, NvSciBufAttrValGpuCache[] shall provide a single value
     * where GPU ID specified in it is of type iGPU and is part of GPU IDs
     * specified in NvSciBufGeneralAttrKey_GpuId. Not satisfying any of the
     * above conditions results in reconciliation failure.
     *
     * During reconciliation, for all the unreconciled NvSciBufAttrLists
     * involved in reconciliation, the input values of this attribute for a
     * particular GPU ID are taken from
     * a) Value specified by unreconciled NvSciBufAttrLists
     * b) Default value based on table specified below if particular
     * unreconciled NvSciBufAttrList does not specify it.
     * The set of input values are then reconciled using AND policy.
     * The policy specified above is applied for ALL the GPU IDs specified in
     * NvSciBufGeneralAttrKey_GpuId.
     *
     * |----------|---------------|-----------|---------------|
     * | GPU TYPE | MEMORY DOMAIN | PLATFORM  | DEFAULT VALUE |
     * |----------|---------------|-----------|---------------|
     * | iGPU     | Sysmem        | Tegra     | TRUE          |
     * |----------|---------------|-----------|---------------|
     * | dGPU     | Sysmem        | Tegra/X86 | FALSE         |
     * |----------|---------------|-----------|---------------|
     * | dGPU     | Vidmem        | Tegra/X86 | TRUE          |
     * |----------|---------------|-----------|---------------|
     *
     * Type: Input/Output attribute
     * Presence: Optional
     *
     * Datatype: NvSciBufAttrValGpuCache[]
     */
    NvSciBufGeneralAttrKey_EnableGpuCache,

    /**
     * An attribute indicating whether application needs to perform GPU cache
     * maintenance before read and after writes. The value of this attribute is
     * set in reconciled NvSciBufAttrList as follows:
     * The value in NvSciBufAttrValGpuCache is set to TRUE for a particular
     * GPU ID in the same struct if,
     * 1) Memory domain is Sysmem AND that particular GPU ID in the
     *     NvSciBufGeneralAttrKey_EnableGpuCache has cacheability value set to
     *     TRUE AND
     *     a) At least one of the GPU IDs in the
     *        NvSciBufGeneralAttrKey_EnableGpuCache has cacheability set to
     *        FALSE. OR
     *     b) At least one of the unreconciled NvSciBufAttrList has requested
     *        CPU access via NvSciBufGeneralAttrKey_NeedCpuAccess OR
     *     c) At least one HW engine will be accessing the buffer.
     * 2) Memory domain is Vidmem AND that particular GPU ID in the
     *     NvSciBufGeneralAttrKey_EnableGpuCache has cacheability value set to
     *     TRUE AND
     *     a) Any of the HW engines accessing the buffer are not cache coherent
     *        with Vidmem
     * It is set to FALSE otherwise.
     *
     * Type: Output attribute
     * Datatype: NvSciBufAttrValGpuCache[]
     */
    NvSciBufGeneralAttrKey_GpuSwNeedCacheCoherency,

    /**
     * Specifies whether to enable/disable GPU compression for the particular
     * GPU.
     * User can specify the value of this attribute in terms of an
     * array of @a NvSciBufAttrValGpuCompression.
     *
     * During reconciliation, if any of the following conditions are satisfied,
     * the reconciliation fails:
     * 1. The GPU ID specified as the member of @a NvSciBufAttrValGpuCompression
     * does not match with any of the GPU ID values specified as an array in
     * NvSciBufGeneralAttrKey_GpuId attribute.
     * 2. For the particular GPU ID specified in the
     * @a NvSciBufAttrValGpuCompression, the value of @a NvSciBufCompressionType
     * is not the same for that particular GPU ID in all of the unreconciled
     * NvSciBufAttrLists that have specified it.
     *
     * If none of the conditions mentioned above for reconciliation failure are
     * met then this attribute is reconciled as follows:
     * 1. If multiple GPUs request compression via
     * NvSciBufGeneralAttrKey_EnableGpuCompression, reconciliation fills
     * NvSciBufCompressionType_None (aka compression is not enabled) for all
     * GPUs specified in NvSciBufGeneralAttrKey_GpuId.
     * 2. If UMDs set any of the non-GPU HW engines in the unreconciled
     * NvSciBufAttrLists implying that at least one non-GPU engine is going to
     * access the buffer represented by NvSciBufObj,
     * reconciliation fills NvSciBufCompressionType_None (aka compression is not
     * enabled) for all GPUs specified in NvSciBufGeneralAttrKey_GpuId.
     * 3. If NvSciBufGeneralAttrKey_NeedCpuAccess attribute is set in at least
     * one of the unreconciled NvSciBufAttrLists implying that CPU access to the
     * buffer represented by NvSciBufObj is needed, reconciliation fills
     * NvSciBufCompressionType_None (aka compression is not enabled) for all
     * GPUs specified in NvSciBufGeneralAttrKey_GpuId.
     * 4. If none of the above conditions are satisfied then the value of
     * NvSciBufCompressionType for that particular GPU ID is set as the matching
     * value specified by all the unreconciled NvSciBufAttrLists that have set
     * it. NvSciBuf then queries lower level NVIDIA driver stack to check if
     * reconciled NvSciBufCompressionType is allowed for the particular GPU.
     * NvSciBuf keeps the reconciled value of NvSciBufCompressionType if this
     * compression type is supported, otherwise NvSciBuf falls back to
     * NvSciBufCompressionType_None.
     * 5. For a particular GPU ID specified in NvSciBufGeneralAttrKey_GpuId,
     * if none of the unreconciled NvSciBufAttrLists specify the compression
     * type needed for that GPU ID via this attribute then NvSciBuf fills
     * the default value of NvSciBufCompressionType_None for that GPU ID in the
     * reconciled NvSciBufAttrList.
     *
     * The number of elements in the array value
     * @a NvSciBufAttrValGpuCompression[] of
     * NvSciBufGeneralAttrKey_EnableGpuCompression attribute in the reconciled
     * NvSciBufAttrList is equal to the number of GPU IDs specified in the
     * NvSciBufGeneralAttrKey_GpuId attribute.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * input unreconciled NvSciBufAttrLists yield
     * @a NvSciBufAttrValGpuCompression value of NvSciBufCompressionType_None
     * for the particular GPU ID while value of the same GPU ID in the
     * reconciled NvSciBufAttrList is other than NvSciBufCompressionType_None.
     *
     * Type: Input/Output attribute
     * Presence: Optional
     *
     * Datatype: NvSciBufAttrValGpuCompression[]
     */
    NvSciBufGeneralAttrKey_EnableGpuCompression,

    /** An attribute indicating location information of late attaching peer(s)
     * which are going to gain access to the allocated NvScibufObj using
     * NvSciBufObjAttachPeer() API.
     *
     * During reconciliation, the value of this attribute in reconciled
     * NvSciBufAttrList is equivalent to the aggregate of all the values
     * specified by all the unreconciled NvSciBufAttrLists involved in
     * reconciliation that have this attribute set.
     *
     * Note:
     * During reconciliation,
     * if NvSciBufGeneralAttrKey_PeerHwEngineArray is not set:
     *   NvSciBuf will consider all Hw engines,
     *   which are reconcilable with other Hw engines present in other
     *   unreconciled NvSciBufAttrList, to align buffer attributes.
     * else if NvSciBufGeneralAttrKey_PeerHwEngineArray is set:
     *   NvSciBuf only consider Hw engines from
     *   NvSciBufGeneralAttrKey_PeerHwEngineArray which are reconcilable with
     *   other Hw engines present in other unreconciled NvSciBufAttrList,
     *   to align buffer attributes.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if value of this
     * attribute set in any of the input unreconciled NvSciBufAttrList(s) is
     * not present in the set of values of this attribute in the provided
     * reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     *
     * Presence: Optional
     * Value: @ref NvSciBufPeerLocationInfo[]
     */
    NvSciBufGeneralAttrKey_PeerLocationInfo,

    /** An attribute indicating list of hardware engines which will access
     * the allocated buffer on late attaching peer(s). These late attaching
     * peer(s) will gain access to the allocated NvSciBufObj using
     * NvSciBufObjAttachPeer() API.
     *
     * During reconciliation, the value of this attribute in reconciled
     * NvSciBufAttrList is equivalent to the aggregate of all the values
     * specified by all the unreconciled NvSciBufAttrLists involved in
     * reconciliation that have this attribute set.
     *
     * Note: During reconciliation, NvSciBuf will consider all Hw engines,
     * which are reconcilable with other Hw engines present in other
     * unreconciled NvSciBufAttrList, to align buffer attributes.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if value of this
     * attribute set in any of the input unreconciled NvSciBufAttrList(s) is
     * not present in the set of values of this attribute in the provided
     * reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     *
     * Presence: Optional
     * Value: @ref NvSciBufPeerHwEngine[]
     */
    NvSciBufGeneralAttrKey_PeerHwEngineArray,

    /**
     * Specifies the size of the NvSciBufType_RawBuffer NvSciBufObj that
     * the underlying buffer allocation satisfies. The input size specified
     * in unreconciled NvSciBufAttrList(s) should be greater than 0.
     *
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_RawBuffer and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     * Unit: byte
     *
     * Value: @c uint64_t
     */
    NvSciBufRawBufferAttrKey_Size   =  NV_SCI_BUF_RAW_BUF_ATTR_KEY_START,

    /** Specifies the alignment requirement of NvSciBufType_RawBuffer. Input
     * alignment should be power of 2. If more than one unreconciled
     * NvSciBufAttrLists specify this input attribute, value in the reconciled
     * NvSciBufAttrList corresponds to maximum of the values specified in all of
     * the unreconciled NvSciBufAttrLists. The value of this attribute is set to
     * default alignment with which buffer is allocated if none of the
     * unreconciled NvSciBufAttrList(s) involved in reconciliation specify this
     * attribute.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_RawBuffer and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Optional
     * Unit: byte
     *
     * Value: @c uint64_t
     *
     * valid input value: value is power of 2.
     */
    NvSciBufRawBufferAttrKey_Align,

    /** Specifies the layout of NvSciBufType_Image: Block-linear or
     * Pitch-linear. If more than one unreconciled NvSciBufAttrLists specify
     * this input attribute, reconciliation is successful if all the input
     * attributes of this type match.
     *
     * Only pitch-linear layout is supported for image-tensor buffer type
     * reconciliation.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @ref NvSciBufAttrValImageLayoutType
     *
     * valid input value: Any value defined by NvSciBufAttrValImageLayoutType
     * enum.
     */
    NvSciBufImageAttrKey_Layout   =    NV_SCI_BUF_IMAGE_ATTR_KEY_START,

    /** Specifies the top padding for the NvSciBufType_Image. If more than one
     * unreconciled NvSciBufAttrLists specify this input attribute,
     * reconciliation is successful if all the input attributes of this
     * type match. This attribute is set to default value of 0 if none of the
     * unreconciled NvSciBufAttrList(s) involved in reconciliation specify the
     * attribute.
     *
     * Padding is not allowed to be specified for image-tensor reconciliation.
     * It is allowed for image only buffer reconciliation.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Optional when surface-based image
     * attributes are not used, and should not be specified otherwise.
     * Unit: pixel
     *
     * Value: @c uint64_t[]
     */
    NvSciBufImageAttrKey_TopPadding,

    /** Specifies the bottom padding for the NvSciBufType_Image. If more than
     * one unreconciled NvSciBufAttrLists specify this input attribute,
     * reconciliation is successful if all the input attributes of this
     * type match. This attribute is set to default value of 0 if none of the
     * unreconciled NvSciBufAttrList(s) involved in reconciliation specify the
     * attribute.
     *
     * Padding is not allowed to be specified for image-tensor reconciliation.
     * It is allowed for image only buffer reconciliation.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Optional when surface-based image
     * attributes are not used, and should not be specified otherwise.
     * Unit: pixel
     *
     * Value: uint64_t[]
     */
    NvSciBufImageAttrKey_BottomPadding,

    /** Specifies the left padding for the NvSciBufType_Image. If more than one
     * unreconciled NvSciBufAttrLists specify this input attribute,
     * reconciliation is successful if all the input attributes of this
     * type match. This attribute is set to default value of 0 if none of the
     * unreconciled NvSciBufAttrList(s) involved in reconciliation specify the
     * attribute.
     *
     * Padding is not allowed to be specified for image-tensor reconciliation.
     * It is allowed for image only buffer reconciliation.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Optional when surface-based image
     * attributes are not used, and should not be specified otherwise.
     * Unit: pixel
     *
     * Value: @c uint64_t[]
     */
    NvSciBufImageAttrKey_LeftPadding,

    /** Specifies the right padding for the NvSciBufType_Image. If more than one
     * unreconciled NvSciBufAttrLists specify this input attribute,
     * reconciliation is successful if all the input attributes of this
     * type match. This attribute is set to default value of 0 if none of the
     * unreconciled NvSciBufAttrList(s) involved in reconciliation specify the
     * attribute.
     *
     * Padding is not allowed to be specified for image-tensor reconciliation.
     * It is allowed for image only buffer reconciliation.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Optional when surface-based image
     * attributes are not used, and should not be specified otherwise.
     * Unit: pixel
     *
     * Value: @c uint64_t[]
     */
    NvSciBufImageAttrKey_RightPadding,

    /** Specifies the VPR flag for the NvSciBufType_Image.
     *
     * During reconciliation, this key is set to true in reconciled
     * NvSciBufAttrList if any of the unreconciled NvSciBufAttrList owned by any
     * peer set it to true, otherwise it is set to false.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is true and value of same attribute in the
     * provided reconciled NvSciBufAttrList is false.
     *
     * Accessibility: Input/Output attribute
     * Presence: Optional
     *
     * Value: @c bool
     */
    NvSciBufImageAttrKey_VprFlag,

    /**
     * Specifies the size of the NvSciBufType_Image NvSciBufObj that the
     * underlying buffer allocation satisfies after successful reconciliation.
     * The output size for this key is computed by aggregating the size of
     * all the planes in the output key NvSciBufImageAttrKey_PlaneAlignedSize.
     *
     * The size is calculated the following way:
     * NvSciBufImageAttrKey_Size = sum of NvSciBufImageAttrKey_PlaneAlignedSize
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t
     */
    NvSciBufImageAttrKey_Size,

    /** Output alignment of the NvSciBufType_Image after successful
     * reconciliation.
     * The output value of this key is same as alignment value of the first
     * plane in the key NvSciBufImageAttrKey_PlaneBaseAddrAlign after
     * reconciliation.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t
     */
    NvSciBufImageAttrKey_Alignment,

    /** Specifies the number of planes for NvSciBufType_Image. If more than one
     * unreconciled NvSciBufAttrLists specify this input attribute,
     * reconciliation is successful if all the input attributes of this
     * type match. If NvSciBufType_Image and NvSciBufType_Tensor are involved in
     * reconciliation and if this attribute is set in any of unreconciled
     * NvSciBufAttrList(s) to be reconciled, the value of this attribute should
     * be 1.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Mandatory when surface-based image
     * attributes are not used, and should not be specified otherwise.
     *
     * Value: @c uint32_t
     *
     * valid input value: 1 <= value <= NV_SCI_BUF_IMAGE_MAX_PLANES
     */
    NvSciBufImageAttrKey_PlaneCount,

    /** Specifies the NvSciBufAttrValColorFmt of the NvSciBufType_Image plane.
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Mandatory when surface-based image
     * attributes are not used, and should not be specified otherwise.
     *
     * Value: @ref NvSciBufAttrValColorFmt[]
     *
     * valid input value: NvSciColor_LowerBound < value < NvSciColor_UpperBound
     */
    NvSciBufImageAttrKey_PlaneColorFormat,

    /** Specifies a set of plane color standards. If more than
     * one unreconciled NvSciBufAttrLists specify this input attribute,
     * reconciliation is successful if all the input attributes of this
     * type match. This attribute is set to implementation chosen default value
     * if none of the unreconciled NvSciBufAttrList(s) involved in
     * reconciliation specify this attribute.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Optional when surface-based image
     * attributes are not used, and should not be specified otherwise.
     *
     * Value: @ref NvSciBufAttrValColorStd[]
     *
     * valid input value: Any value defined by NvSciBufAttrValColorStd enum.
     */
    NvSciBufImageAttrKey_PlaneColorStd,

    /** Specifies the NvSciBufType_Image plane base address alignment for every
     * plane in terms of an array. Input alignment must be power of 2.
     * If more than one unreconciled NvSciBufAttrLists specify this attribute,
     * reconciled NvSciBufAttrList has maximum alignment value per array index
     * of the values specified in unreconciled NvSciBufAttrLists for the same
     * array index. On top of that, for all the HW engines for which buffer is
     * being allocated, if the maximum start address alignment constraint of all
     * the engines taken together is greater than the reconciled alignment value
     * at any index, it is replaced with start address alignment value. In other
     * words,
     * reconciled alignment per array index =
     * MAX(MAX(alignments in unreconciled list at the same index),
     * MAX(start address alignment constraint of all the engines))
     * The value of this attribute is set to default alignment with which buffer
     * is allocated if none of the unreconciled NvSciBufAttrList(s) involved in
     * reconciliation specify this attribute.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Optional when surface-based image
     * attributes are not used, and should not be specified otherwise.
     * Unit: byte
     *
     * Value: @c uint32_t[]
     *
     * valid input value: value is power of 2.
     */
    NvSciBufImageAttrKey_PlaneBaseAddrAlign,

    /** Specifies the NvSciBufType_Image plane width in pixels. If more than
     * one unreconciled NvSciBufAttrLists specify this input attribute,
     * reconciliation is successful if all the input attributes of this
     * type match.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Mandatory when surface-based image
     * attributes are not used, and should not be specified otherwise.
     * Unit: pixel
     *
     * Value: @c uint32_t[]
     */
    NvSciBufImageAttrKey_PlaneWidth,

    /** Specifies the NvSciBufType_Image plane height in number of pixels. If
     * more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. This is Mandatory when surface-based image
     * attributes are not used, and should not be specified otherwise.
     * Unit: pixel
     *
     * Value: @c uint32_t[]
     */
    NvSciBufImageAttrKey_PlaneHeight,

    /** Specifies the NvSciBufType_Image scan type: Progressive or Interlaced.
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes
     * of this type match.
     *
     * @note NvSciBufImageAttrKey_PlaneScanType is deprecated and may be
     * removed in some future release. Use NvSciBufImageAttrKey_ScanType
     * wherever possible.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @ref NvSciBufAttrValImageScanType
     *
     * valid input value: Any value defined by NvSciBufAttrValImageScanType
     * enum.
     */
    NvSciBufImageAttrKey_PlaneScanType = 0x2000e,
    NvSciBufImageAttrKey_ScanType = NvSciBufImageAttrKey_PlaneScanType,

    /** Outputs number of bits per pixel corresponding to the
     * NvSciBufAttrValColorFmt for each plane specified in
     * NvSciBufImageAttrKey_PlaneColorFormat.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     *
     * Value: @c uint32_t[]
     */
    NvSciBufImageAttrKey_PlaneBitsPerPixel,

    /** Indicates the starting offset of the NvSciBufType_Image plane from the
     * first plane.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t[]
     */
    NvSciBufImageAttrKey_PlaneOffset,

    /** Outputs the NvSciBufAttrValDataType of each plane based on the
     * NvSciBufAttrValColorFmt provided in
     * NvSciBufImageAttrKey_PlaneColorFormat for every plane.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     *
     * Value: @ref NvSciBufAttrValDataType[]
     */
    NvSciBufImageAttrKey_PlaneDatatype,

    /** Outputs number of channels per plane.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     *
     * Value: @c uint8_t[]
     */
    NvSciBufImageAttrKey_PlaneChannelCount,

    /** Indicates the offset of the start of the second field, 0 for progressive
     * valid for interlaced.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t[]
     */
    NvSciBufImageAttrKey_PlaneSecondFieldOffset,

    /** Outputs the pitch (aka width in bytes) for every plane.
     *
     * The pitch is calculated the following way (prior to additional alignment
     * constraints from the hardware engines accessing the buffer being
     * considered), such that the pitch is at least:
     *
     * NvSciBufImageAttrKey_PlanePitch =
     *     (NvSciBufImageAttrKey_PlaneWidth * (Bits per pixel for
     *      NvSciBufImageAttrKey_PlaneColorFormat)) / 8
     *
     * This value is then aligned to the maximum of the pitch alignment
     * constraint value of all the HW engines that are going to operate on the
     * buffer using extra padding bytes.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint32_t[]
     */
    NvSciBufImageAttrKey_PlanePitch,

    /** Outputs the aligned height of every plane in terms of number of pixels.
     * This height is calculated by aligning value for every plane provided in
     * NvSciBufImageAttrKey_PlaneHeight with maximum of the height alignment
     * constraints of all the engines that are going to operate on the buffer.
     *
     * The height is calculated the following way:
     * If (NvSciBufImageAttrKey_ScanType == NvSciBufScan_InterlaceType)
     *     NvSciBufImageAttrKey_PlaneAlignedHeight =
     *     (NvSciBufImageAttrKey_PlaneHeight / 2)
     *     This value is aligned to highest height HW constraints among all
     *     the HW engines accessing the buffer
     * Else
     *     NvSciBufImageAttrKey_PlaneAlignedHeight =
     *     NvSciBufImageAttrKey_PlaneHeight
     *     This value is aligned to highest height HW constraints among all
     *     the HW engines accessing the buffer
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: pixel
     *
     * Value: @c uint32_t[]
     */
    NvSciBufImageAttrKey_PlaneAlignedHeight,

    /** Indicates the aligned size of every plane. The size is calculated from
     * the value of NvSciBufImageAttrKey_PlanePitch and
     * NvSciBufImageAttrKey_PlaneAlignedHeight.
     *
     * The size is calculated the following way:
     * If (NvSciBufImageAttrKey_ScanType == NvSciBufScan_InterlaceType)
     *     NvSciBufImageAttrKey_PlaneAlignedSize =
     *         NvSciBufImageAttrKey_PlanePitch *
     *         NvSciBufImageAttrKey_PlaneAlignedHeight * 2
     *     This value is aligned to highest size HW constraints among all
     *     the HW engines accessing the buffer
     * Else
     *     NvSciBufImageAttrKey_PlaneAlignedSize =
     *         NvSciBufImageAttrKey_PlanePitch *
     *         NvSciBufImageAttrKey_PlaneAlignedHeight
     *     This value is aligned to highest size HW constraints among all
     *     the HW engines accessing the buffer
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t[]
     */
    NvSciBufImageAttrKey_PlaneAlignedSize,

    /** Attribute to specify number of NvSciBufType_Image(s) for which buffer
     * should be allocated. If more than one unreconciled NvSciBufAttrLists
     * specify this input attribute, reconciliation is successful if all the
     * input attributes of this type match. This attribute is set to default
     * value of 1 if none of the unreconciled NvSciBufAttrList(s) specify this
     * attribute and the condition for the optional presence of this attribute
     * is satisfied.
     * NvSciBuf supports allocating buffer for single image only and thus, this
     * attribute should be set to 1. A single buffer cannot be allocated for
     * multiple images. Allocating 'N' buffers corresponding to 'N' images is
     * allowed.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory for Image/Tensor reconciliation,
     * Optional otherwise.
     *
     * Value: @c uint64_t
     *
     * valid input value: 1
     */
    NvSciBufImageAttrKey_ImageCount,

    /**
     * Specifies the NvSciBufSurfType. If more than one unreconciled
     * NvSciBufAttrList specifies this input attribute, reconciliation is
     * successful if all the input attributes of this type match. This value is
     * set on the reconciled NvSciBufAttrList. This attribute is unset in the
     * reconciled NvSciBufAttrList if no surface-based image attributes were
     * requested in the unreconciled NvSciBufAttrList(s).
     *
     * During validation of a reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList
     *   when it is set in at least one of the unreconciled NvSciBufAttrList(s)
     *   that are being verified against this reconciled NvSciBufAttrList
     * - The value of this attribute set in any of the input unreconciled
     *   NvSciBufAttrList(s) is not equal to the value of same attribute in the
     *   provided reconciled NvSciBufAttrList.
     *
     * @note This is a convenience attribute key. Such surface-based attribute
     * keys are mutually exclusive with the plane-based attribute keys. If both
     * types of attribute keys are specified then reconciliation will fail.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory when surface-based image attributes are
     * used, and should not be specified otherwise.
     *
     * Value: @ref NvSciBufSurfType
     */
    NvSciBufImageAttrKey_SurfType,

    /**
     * Specifies the NvSciBufSurfMemLayout. If more than one unreconciled
     * NvSciBufAttrList specifies this input attribute, reconciliation is
     * successful if all the input attributes of this type match. This value is
     * set on the reconciled NvSciBufAttrList. This attribute is unset in the
     * reconciled NvSciBufAttrList if no surface-based image attributes were
     * requested in the unreconciled NvSciBufAttrList(s).
     *
     * During validation of a reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList
     *   when it is set in at least one of the unreconciled NvSciBufAttrList(s)
     *   that are being verified against this reconciled NvSciBufAttrList
     * - The value of this attribute set in any of the input unreconciled
     *   NvSciBufAttrList(s) is not equal to the value of same attribute in the
     *   provided reconciled NvSciBufAttrList.
     *
     * @note This is a convenience attribute key. Such surface-based attribute
     * keys are mutually exclusive with the plane-based attribute keys. If both
     * types of attribute keys are specified then reconciliation will fail.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory when surface-based image attributes are
     * used, and should not be specified otherwise.
     *
     * Value: @ref NvSciBufSurfMemLayout
     */
    NvSciBufImageAttrKey_SurfMemLayout,

    /**
     * Specifies the NvSciBufSurfSampleType. If more than one unreconciled
     * NvSciBufAttrList specifies this input attribute, reconciliation is
     * successful if all the input attributes of this type match. This value is
     * set on the reconciled NvSciBufAttrList. This attribute is unset in the
     * reconciled NvSciBufAttrList if no surface-based image attributes were
     * requested in the unreconciled NvSciBufAttrList(s).
     *
     * During validation of a reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList
     *   when it is set in at least one of the unreconciled NvSciBufAttrList(s)
     *   that are being verified against this reconciled NvSciBufAttrList
     * - The value of this attribute set in any of the input unreconciled
     *   NvSciBufAttrList(s) is not equal to the value of same attribute in the
     *   provided reconciled NvSciBufAttrList.
     *
     * @note This is a convenience attribute key. Such surface-based attribute
     * keys are mutually exclusive with the plane-based attribute keys. If both
     * types of attribute keys are specified then reconciliation will fail.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory when surface-based image attributes are
     * used, and should not be specified otherwise.
     *
     * Value: @ref NvSciBufSurfSampleType
     *
     * valid input value:
     */
    NvSciBufImageAttrKey_SurfSampleType,

    /**
     * Specifies the NvSciBufSurfBPC. If more than one unreconciled
     * NvSciBufAttrList specifies this input attribute, reconciliation is
     * successful if all the input attributes of this type match. This value is
     * set on the reconciled NvSciBufAttrList. This attribute is unset in the
     * reconciled NvSciBufAttrList if no surface-based image attributes were
     * requested in the unreconciled NvSciBufAttrList(s).
     *
     * During validation of a reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList
     *   when it is set in at least one of the unreconciled NvSciBufAttrList(s)
     *   that are being verified against this reconciled NvSciBufAttrList
     * - The value of this attribute set in any of the input unreconciled
     *   NvSciBufAttrList(s) is not equal to the value of same attribute in the
     *   provided reconciled NvSciBufAttrList.
     *
     * @note This is a convenience attribute key. Such surface-based attribute
     * keys are mutually exclusive with the plane-based attribute keys. If both
     * types of attribute keys are specified then reconciliation will fail.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory when surface-based image attributes are
     * used, and should not be specified otherwise.
     *
     * Value: @ref NvSciBufSurfBPC
     */
    NvSciBufImageAttrKey_SurfBPC,

    /**
     * Specifies the NvSciSurfComponentOrder. If more than one unreconciled
     * NvSciBufAttrList specifies this input attribute, reconciliation is
     * successful if all the input attributes of this type match. This value is
     * set on the reconciled NvSciBufAttrList. This attribute is unset in the
     * reconciled NvSciBufAttrList if no surface-based image attributes were
     * requested in the unreconciled NvSciBufAttrList(s).
     *
     * During validation of a reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList
     *   when it is set in at least one of the unreconciled NvSciBufAttrList(s)
     *   that are being verified against this reconciled NvSciBufAttrList
     * - The value of this attribute set in any of the input unreconciled
     *   NvSciBufAttrList(s) is not equal to the value of same attribute in the
     *   provided reconciled NvSciBufAttrList.
     *
     * @note This is a convenience attribute key. Such surface-based attribute
     * keys are mutually exclusive with the plane-based attribute keys. If both
     * types of attribute keys are specified then reconciliation will fail.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory when surface-based image attributes are
     * used, and should not be specified otherwise.
     *
     * Value: @ref NvSciBufSurfComponentOrder
     */
    NvSciBufImageAttrKey_SurfComponentOrder,

    /**
     * Specifies the surface base width. If more than one unreconciled
     * NvSciBufAttrList specifies this input attribute, reconciliation is
     * successful if all the input attributes of this type match. This value is
     * set on the reconciled NvSciBufAttrList. This attribute is unset in the
     * reconciled NvSciBufAttrList if no surface-based image attributes were
     * requested in the unreconciled NvSciBufAttrList(s).
     *
     * During validation of a reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList
     *   when it is set in at least one of the unreconciled NvSciBufAttrList(s)
     *   that are being verified against this reconciled NvSciBufAttrList
     * - The value of this attribute set in any of the input unreconciled
     *   NvSciBufAttrList(s) is not equal to the value of same attribute in the
     *   provided reconciled NvSciBufAttrList.
     *
     * @note This is a convenience attribute key. Such surface-based attribute
     * keys are mutually exclusive with the plane-based attribute keys. If both
     * types of attribute keys are specified then reconciliation will fail.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory when surface-based image attributes are
     * used, and should not be specified otherwise.
     * Unit: pixel
     *
     * Value: @c uint32_t
     */
    NvSciBufImageAttrKey_SurfWidthBase,

    /**
     * Specifies the Surface base height. If more than one unreconciled
     * NvSciBufAttrList specifies this input attribute, reconciliation is
     * successful if all the input attributes of this type match. This value is
     * set on the reconciled NvSciBufAttrList. This attribute is unset in the
     * reconciled NvSciBufAttrList if no surface-based image attributes were
     * requested in the unreconciled NvSciBufAttrList(s).
     *
     * During validation of a reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList
     *   when it is set in at least one of the unreconciled NvSciBufAttrList(s)
     *   that are being verified against this reconciled NvSciBufAttrList
     * - The value of this attribute set in any of the input unreconciled
     *   NvSciBufAttrList(s) is not equal to the value of same attribute in the
     *   provided reconciled NvSciBufAttrList.
     *
     * @note This is a convenience attribute key. Such surface-based attribute
     * keys are mutually exclusive with the plane-based attribute keys. If both
     * types of attribute keys are specified then reconciliation will fail.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory when surface-based image attributes are
     * used, and should not be specified otherwise.
     * Unit: pixel
     *
     * Value: @c uint32_t
     */
    NvSciBufImageAttrKey_SurfHeightBase,

    /**
     * Specifies the NvSciBufAttrValColorStd applicable to all the surface's
     * planes. If more than one unreconciled NvSciBufAttrList specifies this
     * input attribute, reconciliation is successful if all the input
     * attributes of this type match. This value is set on the reconciled
     * NvSciBufAttrList. This attribute is unset in the reconciled
     * NvSciBufAttrList if no surface-based image attributes were requested in
     * the unreconciled NvSciBufAttrList(s).
     *
     * During validation of a reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Image and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList
     *   when it is set in at least one of the unreconciled NvSciBufAttrList(s)
     *   that are being verified against this reconciled NvSciBufAttrList
     * - The value of this attribute set in any of the input unreconciled
     *   NvSciBufAttrList(s) is not equal to the value of same attribute in the
     *   provided reconciled NvSciBufAttrList.
     *
     * @note This is a convenience attribute key. Such surface-based attribute
     * keys are mutually exclusive with the plane-based attribute keys. If both
     * types of attribute keys are specified then reconciliation will fail.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Optional when surface-based image attributes are
     * used, and should not be specified otherwise.
     *
     * Value: @ref NvSciBufAttrValColorStd
     *
     * valid input value: Any value defined by NvSciBufAttrValColorStd enum.
     */
    NvSciBufImageAttrKey_SurfColorStd,

    /** Specifies the tensor data type.
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Tensor and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @ref NvSciBufAttrValDataType
     *
     * valid input value: NvSciDataType_Int4 <= value <= NvSciDataType_Float32
     */
    NvSciBufTensorAttrKey_DataType  =  NV_SCI_BUF_TENSOR_ATTR_KEY_START,

    /** Specifies the number of tensor dimensions. A maximum of 8 dimensions are
     * allowed. If more than one unreconciled NvSciBufAttrLists specify this
     * input attribute, reconciliation is successful if all the input attributes
     * of this type match.
     * If NvSciBufType_Image and NvSciBufType_Tensor NvSciBufTypes are used
     * in reconciliation, reconciliation succeeds only if this key is set
     * to 4, since NvSciBuf only supports reconciliation of NvSciBufType_Tensor
     * of NHWC type with NvSciBufType_Image.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Tensor and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @c uint32_t
     *
     * valid input value: 1 <= value <= NV_SCI_BUF_TENSOR_MAX_DIMS
     */
    NvSciBufTensorAttrKey_NumDims,

    /** Specifies the size of each tensor dimension.
     * This attribute takes size value in terms of an array.
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match. Number of elements in value array of this attribute
     * should not be less than value specified by NvSciBufTensorAttrKey_NumDims
     * attribute.
     * @note Array indices are not tied to the semantics of the
     * dimension if NvSciBufType_Tensor is the only NvSciBufType involved
     * in reconciliation. If NvSciBufType_Tensor and NvSciBufType_Image
     * are involved in reconciliation, NvSciBuf only supports
     * reconciliation of NvSciBufType_Image with NHWC NvSciBufType_Tensor
     * where N=1 and thus reconciliation succeeds only if value of
     * dimension 0 is 1 and it matches with value of
     * NvSciBufImageAttrKey_ImageCount, value of dimension 1 matches with value
     * of NvSciBufImageAttrKey_PlaneHeight, value of dimension 2 matches with
     * value of NvSciBufImageAttrKey_PlaneWidth and dimension 3 specifies
     * channel count for NvSciBufAttrValColorFmt specified in
     * NvSciBufTensorAttrKey_PixelFormat key
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Tensor and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @c uint64_t[]
     */
    NvSciBufTensorAttrKey_SizePerDim,

    /** Specifies the alignment constraints per tensor dimension.
     * Number of elements in value array of this attribute should not be less
     * than value specified by NvSciBufTensorAttrKey_NumDims attribute. Value of
     * every element in the value array should be power of two. If more than one
     * unreconciled NvSciBufAttrLists specify this input attribute, value in the
     * reconciled NvSciBufAttrList corresponds to maximum of the values
     * specified in all of the unreconciled NvSciBufAttrLists that have set this
     * attribute. The value of this attribute is set to default alignment with
     * which buffer is allocated if none of the unreconciled NvSciBufAttrList(s)
     * involved in reconciliation specify this attribute and condition for the
     * optional presence of this attribute is satisfied.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Tensor and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory for Tensor only reconciliation, optional
     * otherwise.
     * Unit: byte
     *
     * Value: @c uint32_t[]
     *
     * valid input value: value is power of 2.
     */
    NvSciBufTensorAttrKey_AlignmentPerDim,

    /** Returns the stride value (in bytes) for each tensor dimension.
     * @note The returned array contains stride values in decreasing order.
     * In other words, the index @em 0 of the array will have the largest
     * stride while [@em number-of-dims - 1] index will have the smallest stride.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Tensor and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t[]
     */
    NvSciBufTensorAttrKey_StridesPerDim,

    /** Attribute providing pixel format of the tensor. This key needs to be
     * set only if NvSciBufType_Image and NvSciBufType_Tensor are involved in
     * reconciliation.
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match. Additionally, reconciliation succeeds only if value of
     * this attribute matches with the value of
     * NvSciBufImageAttrKey_PlaneColorFormat in all the input unreconciled
     * NvSciBufAttrList(s) that have set it.
     * Image/Tensor reconciliation only supports NvSciColor_A8B8G8R8 and
     * NvSciColor_Float_A16B16G16R16 color formats as of now. This attribute is
     * set to default value if none of the unreconciled NvSciBufAttrList(s)
     * involved in reconciliation specify this attribute and condition for the
     * optional presence of this attribute is satisfied.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Tensor and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Conditional. Mandatory for Image/Tensor reconciliation,
     * optional otherwise.
     *
     * Value: @ref NvSciBufAttrValColorFmt
     *
     * valid input value: NvSciColor_LowerBound < value < NvSciColor_UpperBound
     */
    NvSciBufTensorAttrKey_PixelFormat,

    /** Attribute providing base address alignment requirements for tensor.
     * Input value provided for this attribute must be power of two. Output
     * value of this attribute is always power of two. If more than one
     * unreconciled NvSciBufAttrLists specify this input attribute, value in the
     * reconciled NvSciBufAttrList corresponds to maximum of the values
     * specified in all of the unreconciled NvSciBufAttrLists that have set this
     * attribute.
     * The value of this attribute is set to default alignment with
     * which buffer is allocated if none of the unreconciled NvSciBufAttrList(s)
     * involved in reconciliation specify this attribute and condition for the
     * optional presence of this attribute is satisfied.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Tensor and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Optional
     * Unit: byte
     *
     * Value: @c uint64_t
     *
     * valid input value: value is power of 2.
     */
    NvSciBufTensorAttrKey_BaseAddrAlign,

    /**
     * Specifies the size of the NvSciBufType_Tensor NvSciBufObj with
     * NvSciBufTensorAttrKey_NumDims tensor dimensions that the underlying
     * buffer allocation satisfies after successful reconciliation.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) contains NvSciBufType_Tensor and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t
     */
    NvSciBufTensorAttrKey_Size,

    /** Specifies the data type of a NvSciBufType_Array.
     *
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match. Upon successful reconciliation, the reconciled value of
     * this attribute is equal to the value of the same attribute in one of the
     * unreconciled NvSciBufAttrLists.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Array and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @ref NvSciBufAttrValDataType
     *
     * valid input value: NvSciDataType_Int4 <= value <= NvSciDataType_Bool
     */
    NvSciBufArrayAttrKey_DataType   =  NV_SCI_BUF_ARRAY_ATTR_KEY_START,

    /** Specifies the stride of each element in the NvSciBufType_Array.
     * Stride must be greater than or equal to size of datatype specified by
     * NvSciBufArrayAttrKey_DataType.
     *
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match. Upon successful reconciliation, the reconciled value of
     * this attribute is equal to the value of the same attribute in one of the
     * unreconciled NvSciBufAttrLists.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Array and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     * Unit: byte
     *
     * Value: @c uint64_t
     */
    NvSciBufArrayAttrKey_Stride,

    /** Specifies the NvSciBufType_Array capacity.
     *
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match. Upon successful reconciliation, the reconciled value of
     * this attribute is equal to the value of the same attribute in one of the
     * unreconciled NvSciBufAttrLists.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Array and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @c uint64_t
     */
    NvSciBufArrayAttrKey_Capacity,

    /**
     * Specifies the size of the NvSciBufType_Array NvSciBufObj that
     * the underlying buffer allocation satisfies after successful
     * reconciliation.
     *
     * During reconciliation, the size is calculated as follows:
     * NvSciBufArrayAttrKey_Size = reconciled value of
     * NvSciBufArrayAttrKey_Capacity * reconciled value of
     * NvSciBufArrayAttrKey_Stride.
     * This value is then aligned to highest data alignment constraints among
     * all the HW engines accessing the buffer.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Array and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t
     */
    NvSciBufArrayAttrKey_Size,

    /** Indicates the base alignment of a NvSciBufType_Array.
     *
     * During reconciliation, the value of this attribute is set as the highest
     * start address alignment among all the HW engines accessing the buffer.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Array and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t
     */
    NvSciBufArrayAttrKey_Alignment,

    /** Specifies the number of levels of images in a pyramid.
     *
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match. Upon successful reconciliation, the reconciled value of
     * this attribute is equal to the value of the same attribute in one of the
     * unreconciled NvSciBufAttrLists.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Pyramid and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @c uint32_t
     *
     * valid input value: 1 <= value <= NV_SCI_BUF_PYRAMID_MAX_LEVELS
     */
    NvSciBufPyramidAttrKey_NumLevels  =  NV_SCI_BUF_PYRAMID_ATTR_KEY_START,

    /** Specifies the scaling factor by which each successive image in a
     * pyramid must be scaled.
     *
     * If more than one unreconciled NvSciBufAttrLists specify this input
     * attribute, reconciliation is successful if all the input attributes of
     * this type match. Upon successful reconciliation, the reconciled value of
     * this attribute is equal to the value of the same attribute in one of the
     * unreconciled NvSciBufAttrLists.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Pyramid and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute set in any of the input unreconciled
     * NvSciBufAttrList(s) is not equal to the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Input/Output attribute
     * Presence: Mandatory
     *
     * Value: @c float
     *
     * valid input value: 0.0f < value <= 1.0f
     */
    NvSciBufPyramidAttrKey_Scale,

    /** Buffer offset per level.
     *
     * During reconciliation, value of this attribute is calculated per level
     * such that offset per level is equal to the number of offset bytes that
     * need to be added from the starting buffer address of the first level to
     * jump to the starting buffer address of the current level.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Pyramid and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t[]
     */
    NvSciBufPyramidAttrKey_LevelOffset,

    /** Buffer size per pyramid level.
     *
     * During reconciliation, values of NvSciBufImageAttrKey_PlaneWidth and
     * NvSciBufImageAttrKey_PlaneHeight in reconciled NvSciBufAttrList are
     * considered for computation of image size for the first level. For
     * subsequent levels, the width and height are scaled down from the previous
     * level by the factor specified in reconciled value of
     * NvSciBufPyramidAttrKey_Scale and buffer size of image for each level is
     * computed as specified in NvSciBufImageAttrKey_Size. The reconciled value
     * of this attribute contains the buffer size of the image for each level.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Pyramid and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: @c uint64_t[]
     */
    NvSciBufPyramidAttrKey_LevelSize,

    /** Alignment attribute of pyramid.
     *
     * During reconciliation, the value of this attribute is assigned the value
     * equal to the value of NvSciBufImageAttrKey_Alignment in the
     * reconciled NvSciBufAttrList.
     *
     * During validation of reconciled NvSciBufAttrList against input
     * unreconciled NvSciBufAttrList(s), validation fails if reconciliation of
     * NvSciBufGeneralAttrKey_Types attribute from the input unreconciled
     * NvSciBufAttrList(s) yields NvSciBufType_Pyramid and any of the
     * following conditions is satisfied:
     * - This attribute is not set in the provided reconciled NvSciBufAttrList.
     * - Value of this attribute reconciled from input unreconciled
     * NvSciBufAttrList(s) is greater than the value of same attribute in the
     * provided reconciled NvSciBufAttrList.
     *
     * Accessibility: Output attribute
     * Unit: byte
     *
     * Value: uint64_t
     */
    NvSciBufPyramidAttrKey_Alignment,

    /** Specifies the maximum number of NvSciBuf attribute keys.
     * The total space for keys is 32K.
     *
     * Value: None
     */
    NvSciBufAttrKey_UpperBound = 0x3ffffffU,

} NvSciBufAttrKey;

/**
 * @}
 */

/**
 * @addtogroup nvscibuf_datatype
 * @{
 */

/**
 * @brief Defines buffer access permissions for NvSciBufObj.
 *
 * @implements{18840072}
 */
typedef enum {
    NvSciBufAccessPerm_Readonly = 1,
    NvSciBufAccessPerm_ReadWrite = 3,
    /** Usage of Auto permissions is restricted only for export, import APIs
     * and shouldn't be used to set value for
     * NvSciBufGeneralAttrKey_RequiredPerm Attribute */
    NvSciBufAccessPerm_Auto,
    NvSciBufAccessPerm_Invalid,
} NvSciBufAttrValAccessPerm;

/**
 * @brief Defines the image layout type for NvSciBufType_Image.
 *
 * @implements{18840075}
 */
typedef enum {
    /**
     * Block linear layout format.
     * A hardware-optimized image layout.
     */
    NvSciBufImage_BlockLinearType,
    /**
     * Pitch linear layout format.
     */
    NvSciBufImage_PitchLinearType,
} NvSciBufAttrValImageLayoutType;

/**
 * @brief Defines the image scan type for NvSciBufType_Image.
 *
 * @implements{18840078}
 */
typedef enum {
    NvSciBufScan_ProgressiveType,
    NvSciBufScan_InterlaceType,
} NvSciBufAttrValImageScanType;

/**
 * @brief Defines the image color formats for NvSciBufType_Image.
 *
 * Color units are composed of sequences of 'words'.
 * Words correspond to 8-, 16-, 32-, or 64-bit data types,
 * though the specific type depends on the color format.
 *
 * Words are separated by underscores.
 * Example : NvSciColor_U8_V8
 *
 * Within a word, color components are ordered from most-significant bit to
 * least-significant bit when reading from left to right.
 * Example:
 * Bit ordering for little endian machine is as follows
 * for NvSciColor_V10U10
 * pattern  VVVVVVVV VV****** UUUUUUUU UU******
 *          +------+ +------+ +------+ +------+
 * bit      31    24 23    16 15     8 7      0
 *          +---------------------------------+
 * pixel                     0
 *
 * Exceptions:
 *   1. NvSciColor_Y8U8Y8V8, NvSciColor_Y8V8Y8U8, NvSciColor_U8Y8V8Y8, NvSciColor_V8Y8U8Y8 follow different component order.
 *      NvSciColor_U8Y8V8Y8 is equavalent to 2 words with Y unique and U/V shared between the words.
 *      NvSciColor_U8Y8V8Y8 : word 0 = NvSciColor_U8_Y8, word 1 = NvSciColor_V8_Y8
 *
 * '*' means undefined bit value
 *
 *
 * NV12 : YUV420 semi-planar surface with U component occupying Least Significant Bit(s)
 * NV21 : YUV420 semi-planar surface with V component occupying Least Significant Bit(s)
 * NV16 : YUV422 semi-planar surface with U component occupying Least Significant Bit(s)
 * NV61 : YUV422 semi-planar surface with V component occupying Least Significant Bit(s)
 * YV12 : YUV420 full planar surface with plane 0 = Y component, plane 1 = U component, plane 2 = V component
 * YV16 : YUV422 full planar surface with plane 0 = Y component, plane 1 = U component, plane 2 = V component
 * YV24 : YUV444 full planar surface with plane 0 = Y component, plane 1 = U component, plane 2 = V component
 *
 *
 * @implements{18840081}
 */
typedef enum {
    NvSciColor_LowerBound,
    /* RAW PACKED */
    /* Bit ordering for little endian machine is as follows
     * for NvSciColor_X12Bayer20GBRG
     * pattern  BBBBBBBB BBBBBBBB BBBB**** ******** GGGGGGGG GGGGGGGG GGGG**** ********
     *          +------+ +------+ +------+ +------+ +------+ +------+ +------+ +------+
     * bit      63    56 55    48 47    40 39    32 31    24 23    16 15     8 7      0
     *          +---------------------------------+ +---------------------------------+
     * pixel                     1                                   0
     *          +---------------------------------------------------------------------+
     * pitch                                       0
     *
     * pattern  GGGGGGGG GGGGGGGG GGGG**** ******** RRRRRRRR RRRRRRRR RRRR**** ********
     *          +------+ +------+ +------+ +------+ +------+ +------+ +------+ +------+
     * bit      63    56 55    48 47    40 39    32 31    24 23    16 15     8 7      0
     *          +---------------------------------+ +---------------------------------+
     * pixel                     1                                   0
     *          +---------------------------------------------------------------------+
     * pitch                                       1
     *
     * '*' means undefined bit value
     */
    NvSciColor_Bayer8RGGB,
    NvSciColor_Bayer8CCCC,
    NvSciColor_Bayer8BGGR,
    NvSciColor_Bayer8GBRG,
    NvSciColor_Bayer8GRBG,
    NvSciColor_Bayer16BGGR,
    NvSciColor_Bayer16CCCC,
    NvSciColor_Bayer16GBRG,
    NvSciColor_Bayer16GRBG,
    NvSciColor_Bayer16RGGB,
    NvSciColor_Bayer16RCCB,
    NvSciColor_Bayer16BCCR,
    NvSciColor_Bayer16CRBC,
    NvSciColor_Bayer16CBRC,
    NvSciColor_Bayer16RCCC,
    NvSciColor_Bayer16CCCR,
    NvSciColor_Bayer16CRCC,
    NvSciColor_Bayer16CCRC,
    NvSciColor_X2Bayer14GBRG,
    NvSciColor_X4Bayer12GBRG,
    NvSciColor_X6Bayer10GBRG,
    NvSciColor_X2Bayer14GRBG,
    NvSciColor_X4Bayer12GRBG,
    NvSciColor_X6Bayer10GRBG,
    NvSciColor_X2Bayer14BGGR,
    NvSciColor_X4Bayer12BGGR,
    NvSciColor_X6Bayer10BGGR,
    NvSciColor_X2Bayer14RGGB,
    NvSciColor_X4Bayer12RGGB,
    NvSciColor_X6Bayer10RGGB,
    NvSciColor_X2Bayer14CCCC,
    NvSciColor_X4Bayer12CCCC,
    NvSciColor_X6Bayer10CCCC,
    NvSciColor_X4Bayer12RCCB,
    NvSciColor_X4Bayer12BCCR,
    NvSciColor_X4Bayer12CRBC,
    NvSciColor_X4Bayer12CBRC,
    NvSciColor_X4Bayer12RCCC,
    NvSciColor_X4Bayer12CCCR,
    NvSciColor_X4Bayer12CRCC,
    NvSciColor_X4Bayer12CCRC,
    NvSciColor_Signed_X2Bayer14CCCC,
    NvSciColor_Signed_X4Bayer12CCCC,
    NvSciColor_Signed_X6Bayer10CCCC,
    NvSciColor_Signed_Bayer16CCCC,
    NvSciColor_FloatISP_Bayer16CCCC,
    NvSciColor_FloatISP_Bayer16RGGB,
    NvSciColor_FloatISP_Bayer16BGGR,
    NvSciColor_FloatISP_Bayer16GRBG,
    NvSciColor_FloatISP_Bayer16GBRG,
    NvSciColor_FloatISP_Bayer16RCCB,
    NvSciColor_FloatISP_Bayer16BCCR,
    NvSciColor_FloatISP_Bayer16CRBC,
    NvSciColor_FloatISP_Bayer16CBRC,
    NvSciColor_FloatISP_Bayer16RCCC,
    NvSciColor_FloatISP_Bayer16CCCR,
    NvSciColor_FloatISP_Bayer16CRCC,
    NvSciColor_FloatISP_Bayer16CCRC,
    NvSciColor_X12Bayer20CCCC,
    NvSciColor_X12Bayer20BGGR,
    NvSciColor_X12Bayer20RGGB,
    NvSciColor_X12Bayer20GRBG,
    NvSciColor_X12Bayer20GBRG,
    NvSciColor_X12Bayer20RCCB,
    NvSciColor_X12Bayer20BCCR,
    NvSciColor_X12Bayer20CRBC,
    NvSciColor_X12Bayer20CBRC,
    NvSciColor_X12Bayer20RCCC,
    NvSciColor_X12Bayer20CCCR,
    NvSciColor_X12Bayer20CRCC,
    NvSciColor_X12Bayer20CCRC,
    NvSciColor_Signed_X12Bayer20CCCC,
    /*
     * Note: This is currently not supported, and setting this attribute key
     * will fail.
     */
    NvSciColor_Signed_X12Bayer20GBRG,

    /* Semiplanar formats */
    /* Bit ordering for little endian machine is as follows
     * for NvSciColor_V8U8
     * pattern  VVVVVVVV UUUUUUUU
     *          +------+ +------+
     * bit      15     8 7      0
     *          +---------------+
     * pixel            0
     *
     * for NvSciColor_U8_V8
     * pattern  VVVVVVVV UUUUUUUU
     *          +------+ +------+
     * bit      15     8 7      0
     *          +---------------+
     * pixel            0
     *
     * for NvSciColor_V10U10
     * pattern  VVVVVVVV VV****** UUUUUUUU UU******
     *          +------+ +------+ +------+ +------+
     * bit      31    24 23    16 15     8 7      0
     *          +---------------------------------+
     * pixel                     0
     *
     * '*' means undefined bit value
     */
    NvSciColor_U8V8,
    /** Note : NvSciColor_U8_V8 will be deprecated in future release.
     *   NvSciColor_V8U8 color format should be used as a replacement.
     *   NvSciColor_U8_V8 and NvSciColor_V8U8 have same bit ordering.
     */
    NvSciColor_U8_V8,
    NvSciColor_V8U8,
    /** Note : NvSciColor_V8_U8 will be deprecated in future release.
     *   NvSciColor_U8V8 color format should be used as a replacement.
     *   NvSciColor_V8_U8 and NvSciColor_U8V8 have same bit ordering.
     */
    NvSciColor_V8_U8,
    NvSciColor_U10V10,
    NvSciColor_V10U10,
    NvSciColor_U12V12,
    NvSciColor_V12U12,
    NvSciColor_U16V16,
    NvSciColor_V16U16,

    /* PLANAR formats */
    /* Bit ordering for little endian machine is as follows
     * for NvSciColor_Y12
     * pattern  YYYYYYYY YYYY****
     *          +------+ +------+
     * bit      15     8 7      0
     *          +---------------+
     * pixel            0
     * '*' means undefined bit value
     */
    NvSciColor_Y8,
    NvSciColor_Y10,
    NvSciColor_Y12,
    NvSciColor_Y16,
    NvSciColor_U8,
    NvSciColor_V8,
    NvSciColor_U10,
    NvSciColor_V10,
    NvSciColor_U12,
    NvSciColor_V12,
    NvSciColor_U16,
    NvSciColor_V16,

    /* Packed YUV formats */
    /* NvSciColor_Y8U8Y8V8, NvSciColor_Y8V8Y8U8, NvSciColor_U8Y8V8Y8, NvSciColor_V8Y8U8Y8 follow
     * different component order than generic word representation.
     *
     * Bit ordering for little endian machine is as follows
     * for NvSciColor_U8Y8V8Y8
     * pattern  YYYYYYYY VVVVVVVV YYYYYYYY UUUUUUUU
     *          +------+ +------+ +------+ +------+
     * bit      31    24 23    16 15     8 7      0
     *          +---------------------------------+
     * pixel                     0
     *
     * for NvSciColor_A16Y16U16V16
     * pattern  AAAAAAAAAAAAAAAA YYYYYYYYYYYYYYYY UUUUUUUUUUUUUUUU VVVVVVVVVVVVVVVV
     *          +--------------+ +--------------+ +--------------+ +--------------+
     * bit      63            48 47            32 31            16 15             0
     *          +-----------------------------------------------------------------+
     * pixel                                     0
     *
     */
    NvSciColor_A8Y8U8V8,
    NvSciColor_Y8U8Y8V8,
    NvSciColor_Y8V8Y8U8,
    NvSciColor_U8Y8V8Y8,
    NvSciColor_V8Y8U8Y8,
    NvSciColor_A16Y16U16V16,

    /* RGBA PACKED */
    /* Bit ordering for little endian machine is as follows
     * for NvSciColor_A2R10G10B10
     * pattern  AARRRRRR RRRRGGGG GGGGGGBB BBBBBBBB
     *          +------+ +------+ +------+ +------+
     * bit      31    24 23    16 15     8 7      0
     *          +---------------------------------+
     * pixel                     0
     *
     */
    NvSciColor_A8,
    NvSciColor_Signed_A8,
    NvSciColor_B8G8R8A8,
    NvSciColor_A8R8G8B8,
    NvSciColor_A8B8G8R8,
    NvSciColor_A2R10G10B10,
    NvSciColor_A16,
    NvSciColor_Signed_A16,
    NvSciColor_Signed_R16G16,
    NvSciColor_A16B16G16R16,
    NvSciColor_Signed_A16B16G16R16,
    NvSciColor_Float_A16B16G16R16,
    NvSciColor_A32,
    NvSciColor_Signed_A32,
    NvSciColor_Float_A16,

    /* 10-bit 4x4 RGB-IR Bayer formats */
    /* Bit ordering for little endian machine is as follows
     * for NvSciColor_X6Bayer10BGGI_RGGI
     * pattern  GGGGGGGG GG****** RRRRRRRR RR****** GGGGGGGG GG****** BBBBBBBB BB******
     *          +------+ +------+ +------+ +------+ +------+ +------+ +------+ +------+
     * bit      63    56 55    48 47    40 39    32 31    24 23    16 15     8 7      0
     *          +---------------+ +---------------+ +---------------+ +---------------+
     * pixel            3                 2                 1                 0
     *          +---------------------------------------------------------------------+
     * pitch                                       0
     *
     * pattern  IIIIIIII II****** GGGGGGGG GG****** IIIIIIII II****** GGGGGGGG GG******
     *          +------+ +------+ +------+ +------+ +------+ +------+ +------+ +------+
     * bit      63    56 55    48 47    40 39    32 31    24 23    16 15     8 7      0
     *          +---------------+ +---------------+ +---------------+ +---------------+
     * pixel            3                 2                 1                 0
     *          +---------------------------------------------------------------------+
     * pitch                                       1
     *
     * pattern  GGGGGGGG GG****** BBBBBBBB BB****** GGGGGGGG GG****** RRRRRRRR RR******
     *          +------+ +------+ +------+ +------+ +------+ +------+ +------+ +------+
     * bit      63    56 55    48 47    40 39    32 31    24 23    16 15     8 7      0
     *          +---------------+ +---------------+ +---------------+ +---------------+
     * pixel            3                 2                 1                 0
     *          +---------------------------------------------------------------------+
     * pitch                                       2
     *
     * pattern  IIIIIIII II****** GGGGGGGG GG****** IIIIIIII II****** GGGGGGGG GG******
     *          +------+ +------+ +------+ +------+ +------+ +------+ +------+ +------+
     * bit      63    56 55    48 47    40 39    32 31    24 23    16 15     8 7      0
     *          +---------------+ +---------------+ +---------------+ +---------------+
     * pixel            3                 2                 1                 0
     *          +---------------------------------------------------------------------+
     * pitch                                       3
     *
     * '*' means undefined bit value
     */
    NvSciColor_X6Bayer10BGGI_RGGI,
    NvSciColor_X6Bayer10GBIG_GRIG,
    NvSciColor_X6Bayer10GIBG_GIRG,
    NvSciColor_X6Bayer10IGGB_IGGR,
    NvSciColor_X6Bayer10RGGI_BGGI,
    NvSciColor_X6Bayer10GRIG_GBIG,
    NvSciColor_X6Bayer10GIRG_GIBG,
    NvSciColor_X6Bayer10IGGR_IGGB,

    /* 12-bit 4x4 RGB-IR Bayer formats */
    NvSciColor_X4Bayer12BGGI_RGGI,
    NvSciColor_X4Bayer12GBIG_GRIG,
    NvSciColor_X4Bayer12GIBG_GIRG,
    NvSciColor_X4Bayer12IGGB_IGGR,
    NvSciColor_X4Bayer12RGGI_BGGI,
    NvSciColor_X4Bayer12GRIG_GBIG,
    NvSciColor_X4Bayer12GIRG_GIBG,
    NvSciColor_X4Bayer12IGGR_IGGB,

    /* 14-bit 4x4 RGB-IR Bayer formats */
    NvSciColor_X2Bayer14BGGI_RGGI,
    NvSciColor_X2Bayer14GBIG_GRIG,
    NvSciColor_X2Bayer14GIBG_GIRG,
    NvSciColor_X2Bayer14IGGB_IGGR,
    NvSciColor_X2Bayer14RGGI_BGGI,
    NvSciColor_X2Bayer14GRIG_GBIG,
    NvSciColor_X2Bayer14GIRG_GIBG,
    NvSciColor_X2Bayer14IGGR_IGGB,

    /* 16-bit 4x4 RGB-IR Bayer formats */
    NvSciColor_Bayer16BGGI_RGGI,
    NvSciColor_Bayer16GBIG_GRIG,
    NvSciColor_Bayer16GIBG_GIRG,
    NvSciColor_Bayer16IGGB_IGGR,
    NvSciColor_Bayer16RGGI_BGGI,
    NvSciColor_Bayer16GRIG_GBIG,
    NvSciColor_Bayer16GIRG_GIBG,
    NvSciColor_Bayer16IGGR_IGGB,

    /* Right-justified Bayer RAW format */
    /* Bit ordering for little endian machine is as follows
     * for NvSciColor_X4Bayer12RGGB_RJ
     * pattern  ****GGGG GGGGGGGG ****RRRR RRRRRRRR
     *          +------+ +------+ +------+ +------+
     * bit      31    24 23    16 15     8 7      0
     *          +---------------+ +---------------+
     * pixel            1                 0
     *          +---------------------------------+
     * pitch                     0
     *
     * pattern  ****BBBB BBBBBBBB ****GGGG GGGGGGGG
     *          +------+ +------+ +------+ +------+
     * bit      31    24 23    16 15     8 7      0
     *          +---------------+ +---------------+
     * pixel            1                 0
     *          +---------------------------------+
     * pitch                     1
     *
     * '*' means undefined bit value
     */
    NvSciColor_X4Bayer12RGGB_RJ,

    /* RGB PLANAR */
    NvSciColor_R8,
    NvSciColor_G8,
    NvSciColor_B8,

    NvSciColor_UpperBound
} NvSciBufAttrValColorFmt;

/**
 * @brief Defines the image color standard for NvSciBufType_Image.
 *
 * @implements{18840084}
 */
typedef enum {
    NvSciColorStd_SRGB,
    NvSciColorStd_REC601_SR,
    NvSciColorStd_REC601_ER,
    NvSciColorStd_REC709_SR,
    NvSciColorStd_REC709_ER,
    NvSciColorStd_REC2020_RGB,
    NvSciColorStd_REC2020_SR,
    NvSciColorStd_REC2020_ER,
    NvSciColorStd_YcCbcCrc_SR,
    NvSciColorStd_YcCbcCrc_ER,
    NvSciColorStd_SENSOR_RGBA,
    NvSciColorStd_REQ2020PQ_ER,
} NvSciBufAttrValColorStd;

/**
 * @brief Surface types
 *
 * @implements{}
 */
typedef enum {
    /** YUV surface */
    NvSciSurfType_YUV,
    /**
     * RGBA surface
     *
     * Note: This is currently not supported, and setting this attribute key
     * will fail.
     */
    NvSciSurfType_RGBA,
    /**
     * RAW surface
     *
     * Note: This is currently not supported, and setting this attribute key
     * will fail.
     */
    NvSciSurfType_RAW,
    NvSciSurfType_MaxValid,
} NvSciBufSurfType;

/**
 * @brief Memory type
 *
 * @implements{}
 */
typedef enum {
    /**
     * Packed format
     *
     * Note: Reconciliation of packed types is supported only for YUV formats (YUV 400).
     */
    NvSciSurfMemLayout_Packed,
    /**
     * Semi-planar format
     */
    NvSciSurfMemLayout_SemiPlanar,
    /**
     * Planar format
     */
    NvSciSurfMemLayout_Planar,
    NvSciSurfMemLayout_MaxValid,
} NvSciBufSurfMemLayout;

/**
 * @brief Subsampling type
 *
 * @implements{}
 */
typedef enum {
    /** 4:2:0 subsampling */
    NvSciSurfSampleType_420,
    /** 4:2:2 subsampling */
    NvSciSurfSampleType_422,
    /** 4:4:4 subsampling */
    NvSciSurfSampleType_444,
    /** 4:2:2 (transposed) subsampling */
    NvSciSurfSampleType_422R,
    /** 4:0:0 subsampling */
    NvSciSurfSampleType_400,
    NvSciSurfSampleType_MaxValid,
} NvSciBufSurfSampleType;

/**
 * @brief Bits Per Component
 *
 * @implements{}
 */
typedef enum {
    /** 16:8:8 bits per component layout */
    NvSciSurfBPC_Layout_16_8_8,
    /** 10:8:8 bits per component layout */
    NvSciSurfBPC_Layout_10_8_8,
    /** 8 bits per component */
    NvSciSurfBPC_8,
    /** 10 bits per component */
    NvSciSurfBPC_10,
    /** 12 bits per component */
    NvSciSurfBPC_12,
    /** 14 bits per component
     *
     * Note: This is aliased to behave the same way as NvSciSurfBPC_16 to
     * represent hardware where 2 bits are unused. */
    NvSciSurfBPC_14,
    /** 16 bits per component */
    NvSciSurfBPC_16,
    NvSciSurfBPC_MaxValid,
} NvSciBufSurfBPC;

/**
 * @brief Component ordering
 *
 * @implements{}
 */
typedef enum {
    /** YUV component order */
    NvSciSurfComponentOrder_YUV,
    /** YVU component order */
    NvSciSurfComponentOrder_YVU,
    /** Luma-only ordering */
    NvSciSurfComponentOrder_Luma,
    NvSciSurfComponentOrder_MaxValid,
} NvSciBufSurfComponentOrder;

/**
 * @brief Defines various numeric datatypes for NvSciBuf.
 *
 * @implements{18840087}
 */
typedef enum {
    NvSciDataType_Int4,
    NvSciDataType_Uint4,
    NvSciDataType_Int8,
    NvSciDataType_Uint8,
    NvSciDataType_Int16,
    NvSciDataType_Uint16,
    NvSciDataType_Int32,
    NvSciDataType_Uint32,
    NvSciDataType_Float16,
    NvSciDataType_Float32,
    NvSciDataType_FloatISP,
    NvSciDataType_Bool,
    NvSciDataType_UpperBound
} NvSciBufAttrValDataType;

/**
 * @brief an enum spcifying various GPU compression values supported by NvSciBuf
 */
typedef enum {
    /**
     * Default value spcifying that GPU compression defaults to incompressible
     * kind. NvSciBuf fills this value in the reconciled NvSciBufAttrList if
     * the GPU compression is not granted for the particular GPU.
     * If compression is not needed, user does not have to explicitly
     * specify this value in the unreconciled NvSciBufAttrList. NvSciBuf does
     * not allow setting this value in the unreconciled NvSciBufAttrList.
     * Attempting to do so results in NvSciBufAttrListSetAttrs() returning an
     * error.
     */
    NvSciBufCompressionType_None,

    /**
     * Enum to request all possible GPU compression including enabling PLC (Post
     * L-2 Compression).
     * CUDA can read/write the GPU compressible memory with PLC enabled.
     * Vulkan can also read/write the GPU compressible memory with PLC
     * enabled.
     * This compression can be requested in CUDA to CUDA, CUDA to Vulkan and
     * Vulkan to Vulkan interop use-cases.
     */
    NvSciBufCompressionType_GenericCompressible,
} NvSciBufCompressionType;

/**
 * @brief Defines GPU ID structure. This structure is used to
 * set the value for NvSciBufGeneralAttrKey_GpuId attribute.
 *
 * @implements{18840093}
 */
typedef struct {
    /** GPU ID. This member is initialized by the successful
     * call to cuDeviceGetUuid() for CUDA usecases */
    uint8_t bytes[16];
} NvSciRmGpuId;

/**
 * Datatype specifying GPU cacheability preference for a particular GPU ID.
 *
 * @implements{}
 */
typedef struct {
    /**
     * GPU ID for which cache preference need to be specified
     */
    NvSciRmGpuId gpuId;

    /**
     * boolean value specifying cacheability preference. TRUE implies caching
     * needs to be enabled, FALSE indicates otherwise.
     */
    bool cacheability;
} NvSciBufAttrValGpuCache;

/**
 * @brief Datatype specifying compression type needed for a particular GPU ID.
 */
typedef struct {
    /**
     * GPU ID for which compression needs to be specified
     */
    NvSciRmGpuId gpuId;

    /**
     * Type of compression
     */
    NvSciBufCompressionType compressionType;
} NvSciBufAttrValGpuCompression;

/**
 * @brief Datatype specifying the surface co-ordinates for
 * @ref NvSciBufObjGetPixels / @ref NvSciBufObjPutPixels functionality.
 * The first pixel in the user-provided plane will be equal to the first pixel
 * represented in the region specified by the NvSciBufRect.
 */
typedef struct {
    /** Left X co-ordinate. Inclusive. */
    uint64_t x0;
    /** Top Y co-ordinate. Inclusive. */
    uint64_t y0;
    /** Right X co-ordinate. Exclusive. */
    uint64_t x1;
    /** Bottom Y co-ordinate. Exclusive. */
    uint64_t y1;
} NvSciBufRect;

/**
 * @brief Enum to identify hardware engines
 *
 * @implements{18840123}
 */
typedef enum {
    NvSciBufHwEngName_Invalid   = 0,
    NvSciBufHwEngName_Display   = 4,
    NvSciBufHwEngName_Isp       = 11,
    NvSciBufHwEngName_Vi        = 12,
    NvSciBufHwEngName_Csi       = 30,
    NvSciBufHwEngName_Vic       = 106,
    NvSciBufHwEngName_Gpu       = 107,
    NvSciBufHwEngName_MSENC     = 109,
    NvSciBufHwEngName_NVDEC     = 117,
    NvSciBufHwEngName_NVJPG     = 118,
    NvSciBufHwEngName_PVA       = 121,
    NvSciBufHwEngName_DLA       = 122,
    NvSciBufHwEngName_PCIe      = 123,
    NvSciBufHwEngName_OFA       = 124,
    NvSciBufHwEngName_NPM       = 125,
    NvSciBufHwEngName_Num       = 126
} NvSciBufHwEngName;

/**
 * @brief Enum to identify the platform on which late attaching peer(s) is
 * running.
 */
typedef enum {
    NvSciBufPlatformName_LowerBound,
    /** Late attaching peer(s) runs on DRIVEOS Orin platform **/
    NvSciBufPlatformName_Orin,
    /** Late attaching peer(s) runs on x86 PG189 platform **/
    NvSciBufPlatformName_PG189,
    /** Late attaching peer(s) runs on x86 PG199 platform **/
    NvSciBufPlatformName_PG199,
    NvSciBufPlatformName_UpperBound
} NvSciBufPlatformName;

/**
 * @brief Datatype specifying hardware engines which will access NvSciBufObj by
 * late attaching peer(s).
 */
PACK_BUF(typedef struct {
    /** Hardware engine identifier which will access the buffer from late
     * attaching peer(s).
     */
    NvSciBufHwEngName engName;
    /** Platform identifier which will access the buffer from late attaching
     * peer(s).
     */
    NvSciBufPlatformName platName;
}) NvSciBufPeerHwEngine;

/**
 * @}
 */

/**
 * @defgroup nvscibuf_attr_datastructures NvSciBuf Data Structures
 * Specifies NvSciBuf data structures.
 * @{
 */

/**
 * @brief top-level container for the following set of
 *        resources: NvSciBufAttrLists, memory objects, and NvSciBufObjs.
 * Any @ref NvSciBufAttrList created or imported using a particular @ref NvSciBufModule
 * is bound to it, along with any @ref NvSciBufObj created or
 * imported using those NvSciBufAttrList(s).
 *
 * @note For any NvSciBuf API call that has more than one input of type
 * NvSciBufModule, NvSciBufAttrList, and/or NvSciBufObj, all such inputs
 * must agree on the NvSciBufModule instance.
 */
typedef struct NvSciBufModuleRec* NvSciBufModule;

/**
 * @brief This structure defines a key/value pair used to get or set
 * the NvSciBufAttrKey(s) and their corresponding values from or to
 * NvSciBufAttrList.
 *
 * @note An array of this structure need to be set in order to
 * allocate a buffer.
 *
 * @implements{18840090}
 */
typedef struct {
     /** NvSciBufAttrKey for which value needs to be set/retrieved. This member
      * is initialized to any one of the NvSciBufAttrKey other than
      * NvSciBufAttrKey_LowerBound and NvSciBufAttrKey_UpperBound */
      NvSciBufAttrKey key;

      /** Pointer to the value corresponding to the attribute.
       * If the value is an array, the pointer points to the first element. */
      const void* value;

      /** Length of the value in bytes */
      size_t len;
} NvSciBufAttrKeyValuePair;

/**
 * A memory object is a container holding the reconciled NvSciBufAttrList
 * defining constraints of the buffer, the handle of the allocated buffer
 * enforcing the buffer access permissions represented by
 * NvSciBufGeneralAttrKey_ActualPerm key in reconciled NvSciBufAttrList
 * and the buffer properties.
 */

/**
 * @brief A reference to a particular Memory object.
 *
 * @note Every @ref NvSciBufObj that has been created but not freed
 * holds a reference to the @ref NvSciBufModule, preventing it
 * from being de-initialized.
 */
typedef struct NvSciBufObjRefRec* NvSciBufObj;

/**
 * @brief A reference, that is not modifiable, to a particular Memory Object.
 */
typedef const struct NvSciBufObjRefRec* NvSciBufObjConst;


/**
 * @brief A container constituting an attribute list which contains
 * - set of NvSciBufAttrKey attributes defining buffer constraints
 * - slotcount defining number of slots in an attribute list
 * - flag specifying if attribute list is reconciled or unreconciled
 *
 * @note Every @ref NvSciBufAttrList that has been created but not freed
 * holds a reference to the @ref NvSciBufModule, preventing it
 * from being de-initialized.
 */
typedef struct NvSciBufAttrListRec* NvSciBufAttrList;

/**
 * @brief Defines the exported form of NvSciBufObj intended to be
 * shared across an NvSciIpc channel. On successful execution of the
 * NvSciBufObjIpcExport(), the permission requested via this API is stored
 * in the NvSciBufObjIpcExportDescriptor to be granted to the NvSciBufObj
 * on import provided the permission requested via the API is not
 * NvSciBufAccessPerm_Auto. If the NvSciBufAccessPerm_Auto permission is
 * requested via the API then the permission stored in the
 * NvSciBufObjIpcExportDescriptor is equal to the maximum value of the
 * permissions requested via NvSciBufGeneralAttrKey_RequiredPerm attribute in
 * all of the unreconciled NvSciBufAttrLists that were exported by the peer to
 * which the NvSciBufObjIpcExportDescriptor is being exported.
 *
 * @implements{18840114}
 */
PACK_BUF(typedef struct {
      /** Exported data (blob) for NvSciBufObj */
      uint64_t data[NVSCIBUF_EXPORT_DESC_SIZE];
}) NvSciBufObjIpcExportDescriptor;

/** @brief Defines Peer location info structure. This structure is used
 * to set location information of late attaching peer to NvScibufObj using
 * NvSciBufObjAttachPeer() API
 *
 * @implements{}
 */
PACK_BUF(typedef struct {
    /** ID of peer SoC, as configured during bind_partition */
    uint32_t socID;
    /** ID of peer guest VM as mentioned in PCT config */
    uint32_t vmID;
    /** Reserved, do not use */
    uint64_t reserved;
}) NvSciBufPeerLocationInfo;

/**
 * @}
 */
