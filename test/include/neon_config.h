/*
 * Application configuration file for Neon.
 */

#ifndef NEON_CONFIG_H_
#define NEON_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEST_DISABLE_DEBUG
#ifdef NCONFIG_ENABLE_DEBUG
#undef NCONFIG_ENABLE_DEBUG
#endif
#define NCONFIG_ENABLE_DEBUG 1
#endif


#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_CONFIG_H_ */
