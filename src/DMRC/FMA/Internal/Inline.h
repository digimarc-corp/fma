#ifndef DMRC_FMA_INTERNAL_INLINE
#define DMRC_FMA_INTERNAL_INLINE

#if DMRC_FMA_FORCE_INLINE
	#ifdef _MSC_VER
		#define dmrc_inline __forceinline
	#elif defined(__GNUC__)
		#define dmrc_inline inline __attribute__((__always_inline__))
	#elif defined(__CLANG__)
		#if __has_attribute(__always_inline__)
			#define dmrc_inline inline __attribute__((__always_inline__))
		#else
			#define dmrc_inline inline
		#endif
	#elif defined(__arm__)
		#define dmrc_inline inline __attribute__((__always_inline__))
	#else
		#define dmrc_inline inline
	#endif
#else
	#define dmrc_inline inline
#endif

#endif // DMRC_FMA_INTERNAL_INLINE
