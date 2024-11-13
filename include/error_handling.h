#ifndef POKEHEARTGOLD_ERROR_HANDLING_H
#define POKEHEARTGOLD_ERROR_HANDLING_H

/*
 * void GF_AssertFail(void)
 *
 * Called when an assertion fails.
 * Do not use this directly.
 * Instead, use the GF_ASSERT macro defined above.
 */
void GF_AssertFail(void);

void tgsm_assert_failed(const char* condition, const char* filename, int line);

#endif // POKEHEARTGOLD_ERROR_HANDLING_H
