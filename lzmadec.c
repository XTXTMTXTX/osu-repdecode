#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#ifndef LZMADEC_H
#define LZMADEC_H
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
#include <inttypes.h>
#ifndef LZMADEC_NO_STDIO
#include <stdio.h>
#endif
#define LZMADEC_MINIMUM_SIZE 18
#define LZMADEC_OK                0
#define LZMADEC_STREAM_END        1
#define LZMADEC_HEADER_ERROR    (-2)
#define LZMADEC_DATA_ERROR      (-3)
#define LZMADEC_MEM_ERROR       (-4)
#define LZMADEC_BUF_ERROR       (-5)
#define LZMADEC_SEQUENCE_ERROR  (-6)
typedef struct {
	uint8_t *next_in;
	size_t avail_in;
	uint_fast64_t total_in;

	uint8_t *next_out;
	size_t avail_out;
	uint_fast64_t total_out;

	void *state;

	void *(*lzma_alloc)(void *, size_t, size_t);
	void (*lzma_free)(void *, void *);
	void *opaque;
} lzmadec_stream;

typedef struct {
	uint_fast64_t uncompressed_size;
	uint_fast32_t dictionary_size;
	uint_fast32_t internal_data_size;
	uint_fast8_t is_streamed;
	uint_fast8_t pb;
	uint_fast8_t lp;
	uint_fast8_t lc;
} lzmadec_info;

#ifndef LZMADEC_NO_STDIO
typedef void lzmadec_FILE;
#endif
extern int_fast8_t lzmadec_buffer (uint8_t *dest, size_t *dest_len,uint8_t *source, const size_t source_len);
extern int_fast8_t lzmadec_init (lzmadec_stream *strm);
extern int_fast8_t
lzmadec_decode (lzmadec_stream *strm, const int_fast8_t finish_decoding);
int_fast8_t lzmadec_end (lzmadec_stream *strm);
extern int_fast8_t lzmadec_buffer_info (
		lzmadec_info *info, const uint8_t *buffer, const size_t len);
extern const uint8_t *lzmadec_version (void);
#ifndef LZMADEC_NO_STDIO
extern lzmadec_FILE *lzmadec_open (const char *path);
extern lzmadec_FILE *lzmadec_dopen (int fd);
extern ssize_t lzmadec_read (lzmadec_FILE *file, uint8_t *buf, size_t len);
extern uint8_t *lzmadec_gets (lzmadec_FILE *file, uint8_t *buf, size_t len);
extern int lzmadec_getc (lzmadec_FILE *file);
extern int_fast8_t lzmadec_seek (lzmadec_FILE *file, off_t offset, int whence);
extern off_t lzmadec_tell (lzmadec_FILE *file);
extern int_fast8_t lzmadec_rewind (lzmadec_FILE *file);
extern int_fast8_t lzmadec_eof (lzmadec_FILE *file);
extern int_fast8_t lzmadec_close (lzmadec_FILE *file);
#endif
#ifdef __cplusplus
}
#endif
#endif
#define CProb uint32_t
#define LZMA_BASE_SIZE 1846
#define LZMA_LIT_SIZE 768
#define LZMA_IN_BUFFER_SIZE 4096
#define LZMA_MINIMUM_COMPRESSED_FILE_SIZE 18
#define LZMADEC_STATUS_UNINITIALIZED 0
#define LZMADEC_STATUS_RUNNING       1
#define LZMADEC_STATUS_FINISHING     2
#define LZMADEC_STATUS_STREAM_END    3
#define LZMADEC_STATUS_ERROR       (-1)
#define LZMA_NUM_TOP_BITS 24
#define LZMA_TOP_VALUE ((uint32_t)1 << LZMA_NUM_TOP_BITS)
#define LZMA_NUM_BIT_MODEL_TOTAL_BITS 11
#define LZMA_BIT_MODEL_TOTAL (1 << LZMA_NUM_BIT_MODEL_TOTAL_BITS)
#define LZMA_NUM_MOVE_BITS 5
#define LZMA_NUM_POS_BITS_MAX 4
#define LZMA_NUM_POS_STATES_MAX (1 << LZMA_NUM_POS_BITS_MAX)
#define LZMA_LEN_NUM_LOW_BITS 3
#define LZMA_LEN_NUM_LOW_SYMBOLS (1 << LZMA_LEN_NUM_LOW_BITS)
#define LZMA_LEN_NUM_MID_BITS 3
#define LZMA_LEN_NUM_MID_SYMBOLS (1 << LZMA_LEN_NUM_MID_BITS)
#define LZMA_LEN_NUM_HIGH_BITS 8
#define LZMA_LEN_NUM_HIGH_SYMBOLS (1 << LZMA_LEN_NUM_HIGH_BITS)
#define LZMA_LEN_CHOICE 0
#define LZMA_LEN_CHOICE2 (LZMA_LEN_CHOICE + 1)
#define LZMA_LEN_LOW (LZMA_LEN_CHOICE2 + 1)
#define LZMA_LEN_MID (LZMA_LEN_LOW + (LZMA_NUM_POS_STATES_MAX << LZMA_LEN_NUM_LOW_BITS))
#define LZMA_LEN_HIGH (LZMA_LEN_MID + (LZMA_NUM_POS_STATES_MAX << LZMA_LEN_NUM_MID_BITS))
#define LZMA_NUM_LEN_PROBS (LZMA_LEN_HIGH + LZMA_LEN_NUM_HIGH_SYMBOLS)
#define LZMA_NUM_STATES 12
#define LZMA_NUM_LIT_STATES 7
#define LZMA_START_POS_MODEL_INDEX 4
#define LZMA_END_POS_MODEL_INDEX 14
#define LZMA_NUM_FULL_DISTANCES (1 << (LZMA_END_POS_MODEL_INDEX >> 1))
#define LZMA_NUM_POS_SLOT_BITS 6
#define LZMA_NUM_LEN_TO_POS_STATES 4
#define LZMA_NUM_ALIGN_BITS 4
#define LZMA_ALIGN_TABLE_SIZE (1 << LZMA_NUM_ALIGN_BITS)
#define LZMA_MATCH_MIN_LEN 2
#define LZMA_IS_MATCH 0
#define LZMA_IS_REP (LZMA_IS_MATCH + (LZMA_NUM_STATES << LZMA_NUM_POS_BITS_MAX))
#define LZMA_IS_REP_G0 (LZMA_IS_REP + LZMA_NUM_STATES)
#define LZMA_IS_REP_G1 (LZMA_IS_REP_G0 + LZMA_NUM_STATES)
#define LZMA_IS_REP_G2 (LZMA_IS_REP_G1 + LZMA_NUM_STATES)
#define LZMA_IS_REP0_LONG (LZMA_IS_REP_G2 + LZMA_NUM_STATES)
#define LZMA_POS_SLOT (LZMA_IS_REP0_LONG + (LZMA_NUM_STATES << LZMA_NUM_POS_BITS_MAX))
#define LZMA_SPEC_POS (LZMA_POS_SLOT + (LZMA_NUM_LEN_TO_POS_STATES << LZMA_NUM_POS_SLOT_BITS))
#define LZMA_ALIGN (LZMA_SPEC_POS + LZMA_NUM_FULL_DISTANCES - LZMA_END_POS_MODEL_INDEX)
#define LZMA_LEN_CODER (LZMA_ALIGN + LZMA_ALIGN_TABLE_SIZE)
#define LZMA_REP_LEN_CODER (LZMA_LEN_CODER + LZMA_NUM_LEN_PROBS)
#define LZMA_LITERAL (LZMA_REP_LEN_CODER + LZMA_NUM_LEN_PROBS)
#define LZMA_REQUIRED_IN_BUFFER_SIZE ((23 * (LZMA_NUM_BIT_MODEL_TOTAL_BITS - LZMA_NUM_MOVE_BITS + 1) + 26 + 9) / 8)
#if LZMA_LITERAL != LZMA_BASE_SIZE
#error BUG: LZMA_LITERAL != LZMA_BASE_SIZE
#endif
#if LZMA_IN_BUFFER_SIZE <= LZMA_REQUIRED_IN_BUFFER_SIZE
#error LZMA_IN_BUFFER_SIZE <= LZMA_REQUIRED_IN_BUFFER_SIZE
#error Fix by increasing LZMA_IN_BUFFER_SIZE.
#endif
#ifndef MIN
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#endif
typedef struct {
	unsigned char buffer[LZMA_IN_BUFFER_SIZE + LZMA_REQUIRED_IN_BUFFER_SIZE];
	unsigned char *buffer_position;
	size_t buffer_size;
	int_fast8_t status;
	uint_fast32_t dictionary_size;
	uint8_t *dictionary;
	uint_fast64_t uncompressed_size;
	uint_fast8_t streamed;
	uint32_t pos_state_mask;
	uint32_t literal_pos_mask;
	uint_fast8_t pb;
	uint_fast8_t lp;
	uint_fast8_t lc;
	CProb *probs;
	uint32_t range;
	uint32_t code;
	uint_fast32_t dictionary_position;
	uint32_t distance_limit;
	uint32_t rep0, rep1, rep2, rep3;
	int state;
	int len;
} lzmadec_state;
#ifndef UINT64_MAX
#define UINT64_MAX (~(uint64_t)0)
#endif
#define STATE ((lzmadec_state*)(strm->state))
static void *lzmadec_alloc (void *opaque, size_t nmemb, size_t size);
static void lzmadec_free (void *opaque, void *addr);
static int_fast8_t lzmadec_internal_init (lzmadec_stream *strm);
static inline int_fast8_t lzmadec_decode_main (
    lzmadec_stream *strm,
    const int_fast8_t finish_decoding);
static int_fast8_t lzmadec_header_properties (
    uint_fast8_t *pb,
    uint_fast8_t *lp,
    uint_fast8_t *lc,
    const uint8_t c);
static int_fast8_t lzmadec_header_dictionary (
    uint_fast32_t *size,
    const uint8_t *buffer);
static void lzmadec_header_uncompressed (
    uint_fast64_t *size,
    uint_fast8_t *is_streamed,
    const uint8_t *buffer);
extern int_fast8_t lzmadec_init (lzmadec_stream *strm) {
	if (strm->lzma_alloc == NULL)
		strm->lzma_alloc = lzmadec_alloc;
	if (strm->lzma_free == NULL)
		strm->lzma_free = lzmadec_free;
	strm->total_in = 0;
	strm->total_out = 0;
	strm->state = (lzmadec_state*)((strm->lzma_alloc)(strm->opaque, 1, sizeof (lzmadec_state)));
	if (strm->state == NULL)
		return LZMADEC_MEM_ERROR;
	STATE->probs = NULL;
	STATE->dictionary = NULL;
	STATE->status = LZMADEC_STATUS_UNINITIALIZED;
	if (strm->avail_in >= LZMA_MINIMUM_COMPRESSED_FILE_SIZE) {
		return (lzmadec_internal_init (strm));
	}
	return LZMADEC_OK;
}
extern int_fast8_t lzmadec_decode (lzmadec_stream *strm, const int_fast8_t finish_decoding) {
	if (strm == NULL || STATE == NULL)
		return LZMADEC_SEQUENCE_ERROR;
	switch (STATE->status) {
		case LZMADEC_STATUS_UNINITIALIZED:
			if (strm->avail_in < LZMA_MINIMUM_COMPRESSED_FILE_SIZE)
				return LZMADEC_BUF_ERROR;
			if (lzmadec_internal_init (strm) != LZMADEC_OK)
				return LZMADEC_HEADER_ERROR;
		case LZMADEC_STATUS_RUNNING:
			if (strm->total_out < STATE->uncompressed_size)
				break;
			if (strm->total_out > STATE->uncompressed_size)
				return LZMADEC_DATA_ERROR;
			STATE->status = LZMADEC_STATUS_STREAM_END;
		case LZMADEC_STATUS_FINISHING:
			if (!finish_decoding)
				return LZMADEC_SEQUENCE_ERROR;
			if (strm->total_out > STATE->uncompressed_size)
				return LZMADEC_DATA_ERROR;
			if (strm->total_out <  STATE->uncompressed_size)
				break;
		case LZMADEC_STATUS_STREAM_END:
			return LZMADEC_STREAM_END;
		case LZMADEC_STATUS_ERROR:
		default:
			return LZMADEC_SEQUENCE_ERROR;
	}
	return (lzmadec_decode_main(strm, finish_decoding));
}
extern int_fast8_t lzmadec_end (lzmadec_stream *strm) {
	if (strm == NULL || STATE == NULL)
		return LZMADEC_SEQUENCE_ERROR;
	(strm->lzma_free)(strm->opaque, STATE->dictionary);
	STATE->dictionary = NULL;
	(strm->lzma_free)(strm->opaque, STATE->probs);
	STATE->probs = NULL;
	(strm->lzma_free)(strm->opaque, strm->state);
	strm->state = NULL;
	return LZMADEC_OK;
}
extern int_fast8_t
lzmadec_buffer_info (lzmadec_info *info, const uint8_t *buffer, const size_t len) {
	if (len < 13)
		return LZMADEC_BUF_ERROR;
	if (lzmadec_header_properties (&info->pb, &info->lp, &info->lc,
	                               buffer[0]) != LZMADEC_OK)
		return LZMADEC_HEADER_ERROR;
	if (LZMADEC_OK != lzmadec_header_dictionary (
	            &info->dictionary_size, buffer + 1))
		return LZMADEC_HEADER_ERROR;
	lzmadec_header_uncompressed (&info->uncompressed_size,
	                             &info->is_streamed, buffer + 5);
	return LZMADEC_OK;
}
static void *lzmadec_alloc (void *opaque, size_t nmemb, size_t size) {
	return (malloc (nmemb * size));
}
static void
lzmadec_free (void *opaque, void *addr) {
	free (addr);
}
static int_fast8_t lzmadec_header_properties (
    uint_fast8_t *pb, uint_fast8_t *lp, uint_fast8_t *lc, const uint8_t c) {
	if (c > (9 * 5 * 5))
		return LZMADEC_HEADER_ERROR;
	*pb = c / (9 * 5);        /* 0 <= pb <= 4 */
	*lp = (c % (9 * 5)) / 9;  /* 0 <= lp <= 4 */
	*lc = c % 9;              /* 0 <= lc <= 8 */
	assert (*pb < 5 && *lp < 5 && *lc < 9);
	return LZMADEC_OK;
}
static int_fast8_t lzmadec_header_dictionary (uint_fast32_t *size, const uint8_t *buffer) {
	uint_fast32_t i;
	*size = 0;
	for (i = 0; i < 4; i++)
		*size += (uint_fast32_t)(*buffer++) << (i * 8);
	if (*size > (1 << 28))
		return LZMADEC_HEADER_ERROR;
	return LZMADEC_OK;
}
static void lzmadec_header_uncompressed (uint_fast64_t *size, uint_fast8_t *is_streamed,
        const uint8_t *buffer) {
	uint_fast32_t i;
	*size = 0;
	for (i = 0; i < 8; i++) {
		*size += (uint_fast64_t)buffer[i] << (i * 8);
		if (buffer[i] != 255)
			*is_streamed = 0;
	}
	assert ((*is_streamed == 1 && *size == UINT64_MAX)
	        || (*is_streamed == 0 && *size < UINT64_MAX));
}
static int_fast8_t lzmadec_internal_init (lzmadec_stream *strm) {
	uint_fast32_t i;
	uint32_t num_probs;
	size_t lzmadec_num_probs;
	if (STATE->probs != NULL || STATE->dictionary != NULL
	        || STATE->status != LZMADEC_STATUS_UNINITIALIZED)
		return LZMADEC_SEQUENCE_ERROR;
	if (strm->avail_in < LZMA_MINIMUM_COMPRESSED_FILE_SIZE)
		return LZMADEC_BUF_ERROR;
	if (lzmadec_header_properties (&STATE->pb, &STATE->lp, &STATE->lc, *strm->next_in) != LZMADEC_OK)
		return LZMADEC_HEADER_ERROR;
	strm->next_in++;
	strm->avail_in--;
	STATE->pos_state_mask = (1 << STATE->pb) - 1;
	STATE->literal_pos_mask = (1 << STATE->lp) - 1;
	lzmadec_header_dictionary (&STATE->dictionary_size, strm->next_in);
	strm->next_in += 4;
	strm->avail_in -= 4;
	lzmadec_header_uncompressed (&STATE->uncompressed_size,
	                             &STATE->streamed, strm->next_in);
	strm->next_in += 8;
	strm->avail_in -= 8;
	lzmadec_num_probs = (LZMA_BASE_SIZE
	                     + (LZMA_LIT_SIZE << (STATE->lc + STATE->lp)));
	STATE->probs = (CProb *)((strm->lzma_alloc)(strm->opaque, 1,
	                         lzmadec_num_probs * sizeof(CProb)));
	if (STATE->probs == NULL)
		return LZMADEC_MEM_ERROR;
	if (STATE->dictionary_size == 0)
		STATE->dictionary_size = 1;
	STATE->dictionary = (unsigned char*)((strm->lzma_alloc)(
	        strm->opaque, 1, STATE->dictionary_size));
	if (STATE->dictionary == NULL) {
		(strm->lzma_free)(strm->opaque, STATE->probs);
		return LZMADEC_MEM_ERROR;
	}
	num_probs = LZMA_BASE_SIZE
	            + ((CProb)LZMA_LIT_SIZE << (STATE->lc + STATE->lp));
	for (i = 0; i < num_probs; i++)
		STATE->probs[i] = 1024;
	STATE->code = 0;
	for (i = 0; i < 5; i++)
		STATE->code = (STATE->code << 8) | (uint32_t)(*strm->next_in++);
	strm->avail_in -= 5;
	memset (STATE->buffer, 0,
	        LZMA_IN_BUFFER_SIZE + LZMA_REQUIRED_IN_BUFFER_SIZE);
	STATE->rep0 = 1;
	STATE->rep1 = 1;
	STATE->rep2 = 1;
	STATE->rep3 = 1;
	STATE->state = 0;
	strm->total_out = 0;
	STATE->distance_limit = 0;
	STATE->dictionary_position = 0;
	STATE->dictionary[STATE->dictionary_size - 1] = 0;
	STATE->buffer_size = 0;
	STATE->buffer_position = STATE->buffer;
	STATE->len = 0;
	STATE->range = 0xFFFFFFFF;
	STATE->status = LZMADEC_STATUS_RUNNING;
	return LZMADEC_OK;
}

#define RC_NORMALIZE \
	if (range < LZMA_TOP_VALUE) { \
		range <<= 8; \
		code = (code << 8) | *buffer++; \
	}

#define IfBit0(p) \
	RC_NORMALIZE; \
	bound = (range >> LZMA_NUM_BIT_MODEL_TOTAL_BITS) * *(p); \
	if (code < bound)

#define UpdateBit0(p) \
	range = bound; \
	*(p) += (LZMA_BIT_MODEL_TOTAL - *(p)) >> LZMA_NUM_MOVE_BITS;

#define UpdateBit1(p) \
	range -= bound; \
	code -= bound; \
	*(p) -= (*(p)) >> LZMA_NUM_MOVE_BITS;

#define RC_GET_BIT2(p, mi, A0, A1) \
	IfBit0(p) { \
		UpdateBit0(p); \
		mi <<= 1; \
		A0; \
	} else { \
		UpdateBit1(p); \
		mi = (mi + mi) + 1; \
		A1; \
	}

#define RC_GET_BIT(p, mi) RC_GET_BIT2(p, mi, ; , ;)

#define RangeDecoderBitTreeDecode(probs, numLevels, res) \
	{ \
		int i_ = numLevels; \
		res = 1; \
		do { \
			CProb *p_ = probs + res; \
			RC_GET_BIT(p_, res) \
		} while(--i_ != 0); \
		res -= (1 << numLevels); \
	}

static inline int_fast8_t
lzmadec_decode_main (lzmadec_stream *strm, const int_fast8_t finish_decoding) {
	unsigned char *next_out = strm->next_out;
	unsigned char *next_in = strm->next_in;
	size_t avail_in = strm->avail_in;
	uint64_t total_out = strm->total_out;
	/* strm->state-> */
	const int_fast8_t lc = STATE->lc;
	const uint32_t pos_state_mask = STATE->pos_state_mask;
	const uint32_t literal_pos_mask = STATE->literal_pos_mask;
	const uint32_t dictionary_size = STATE->dictionary_size;
	unsigned char *dictionary = STATE->dictionary;
	/*	int_fast8_t streamed;*/ /* boolean */
	CProb *p = STATE->probs;
	uint32_t range = STATE->range;
	uint32_t code = STATE->code;
	uint32_t dictionary_position = STATE->dictionary_position;
	uint32_t distance_limit = STATE->distance_limit;
	uint32_t rep0 = STATE->rep0;
	uint32_t rep1 = STATE->rep1;
	uint32_t rep2 = STATE->rep2;
	uint32_t rep3 = STATE->rep3;
	int state = STATE->state;
	int len = STATE->len;
	unsigned char *buffer_start = STATE->buffer;
	size_t buffer_size = STATE->buffer_size;
	/* Other variable initializations */
	int_fast8_t i; /* Temporary variable for loop indexing */
	unsigned char *next_out_end = next_out + strm->avail_out;
	unsigned char *buffer = STATE->buffer_position;

	/* This should have been verified in lzmadec_decode() already: */
	assert (STATE->uncompressed_size > total_out);
	/* With non-streamed LZMA stream the output has to be limited. */
	if (STATE->uncompressed_size - total_out < strm->avail_out) {
		next_out_end = next_out + (STATE->uncompressed_size - total_out);
	}

	/* The main loop */
	while (1) {
		assert (len >= 0);
		assert (state >= 0);
		/* Copy uncompressed data to next_out: */
		{
			unsigned char *foo = next_out;
			while (len != 0 && next_out != next_out_end) {
				uint32_t pos = dictionary_position - rep0;
				if (pos >= dictionary_size)
					pos += dictionary_size;
				*next_out++ = dictionary[dictionary_position] = dictionary[pos];
				if (++dictionary_position == dictionary_size)
					dictionary_position = 0;
				len--;
			}
			total_out += next_out - foo;
		}

		/* Fill the internal input buffer: */
		{
			size_t avail_buf;
			/* Check for overflow (invalid input) */
			if (buffer > buffer_start + LZMA_IN_BUFFER_SIZE)
				return LZMADEC_DATA_ERROR;
			/* Calculate how much data is unread in the buffer: */
			avail_buf = buffer_size - (buffer - buffer_start);

			/* Copy more data to the buffer if needed: */
			if (avail_buf < LZMA_REQUIRED_IN_BUFFER_SIZE) {
				const size_t copy_size = MIN (avail_in,
				                              LZMA_IN_BUFFER_SIZE - avail_buf);
				if (avail_buf > 0)
					memmove (buffer_start, buffer, avail_buf);
				memcpy (buffer_start + avail_buf,
				        next_in, copy_size);
				buffer = buffer_start;
				next_in += copy_size;
				avail_in -= copy_size;
				buffer_size = avail_buf + copy_size;
			}
		}

		/* Decoder cannot continue if there is
		   - no output space available
		   - less data in the input buffer than a single decoder pass
		     could consume; decoding is still continued if the callee
		     has marked that all available input data has been given. */
		if ((next_out == next_out_end)
		        || (!finish_decoding
		            && buffer_size < LZMA_REQUIRED_IN_BUFFER_SIZE))
			break;

		assert (STATE->status != LZMADEC_STATUS_FINISHING);

		/* The rest of the main loop can at maximum
		   - read at maximum of LZMA_REQUIRED_IN_BUFFER_SIZE bytes
		     from the buffer[]
		   - write one byte to next_out. */
		{
			CProb *prob;
			uint32_t bound;
			int_fast32_t posState = (int_fast32_t)(total_out & pos_state_mask);
			prob = p + LZMA_IS_MATCH + (state << LZMA_NUM_POS_BITS_MAX) + posState;
			IfBit0(prob) {
				int_fast32_t symbol = 1;
				UpdateBit0(prob)
				prob = p + LZMA_LITERAL + (LZMA_LIT_SIZE *
				                           (((total_out & literal_pos_mask) << lc)
				                            + ((dictionary_position != 0
				                                ? dictionary[dictionary_position - 1]
				                                : dictionary[dictionary_size - 1])
				                               >> (8 - lc))));
				if (state >= LZMA_NUM_LIT_STATES) {
					int_fast32_t matchByte;
					uint32_t pos = dictionary_position - rep0;
					if (pos >= dictionary_size)
						pos += dictionary_size;
					matchByte = dictionary[pos];
					do {
						int_fast32_t bit;
						CProb *probLit;
						matchByte <<= 1;
						bit = (matchByte & 0x100);
						probLit = prob + 0x100 + bit + symbol;
						RC_GET_BIT2(probLit, symbol,
						            if (bit != 0) break,
						            if (bit == 0) break)
							} while (symbol < 0x100);
				}
				while (symbol < 0x100) {
					CProb *probLit = prob + symbol;
					RC_GET_BIT(probLit, symbol)
				}

				if (distance_limit < dictionary_size)
					distance_limit++;

				/* Eliminate? */
				*next_out++ = dictionary[dictionary_position]
				              = (char)symbol;
				if (++dictionary_position == dictionary_size)
					dictionary_position = 0;
				total_out++;

				if (state < 4)
					state = 0;
				else if (state < 10)
					state -= 3;
				else
					state -= 6;

				continue;
			}

			UpdateBit1(prob);
			prob = p + LZMA_IS_REP + state;
			IfBit0(prob) {
				UpdateBit0(prob);
				rep3 = rep2;
				rep2 = rep1;
				rep1 = rep0;
				state = state < LZMA_NUM_LIT_STATES ? 0 : 3;
				prob = p + LZMA_LEN_CODER;
			}
			else {
				UpdateBit1(prob);
				prob = p + LZMA_IS_REP_G0 + state;
				IfBit0(prob) {
					UpdateBit0(prob);
					prob = p + LZMA_IS_REP0_LONG + (state
					                                << LZMA_NUM_POS_BITS_MAX)
					       + posState;
					IfBit0(prob) {
						UpdateBit0(prob);
						if (distance_limit == 0)
							return LZMADEC_DATA_ERROR;
						if (distance_limit < dictionary_size)
							distance_limit++;
						state = state < LZMA_NUM_LIT_STATES ? 9 : 11;
						len++;
						continue;
					}
					else {
						UpdateBit1(prob);
					}
				}
				else {
					uint32_t distance;
					UpdateBit1(prob);
					prob = p + LZMA_IS_REP_G1 + state;
					IfBit0(prob) {
						UpdateBit0(prob);
						distance = rep1;
					}
					else {
						UpdateBit1(prob);
						prob = p + LZMA_IS_REP_G2 + state;
						IfBit0(prob) {
							UpdateBit0(prob);
							distance = rep2;
						}
						else {
							UpdateBit1(prob);
							distance = rep3;
							rep3 = rep2;
						}
						rep2 = rep1;
					}
					rep1 = rep0;
					rep0 = distance;
				}
				state = state < LZMA_NUM_LIT_STATES ? 8 : 11;
				prob = p + LZMA_REP_LEN_CODER;
			}

			{
				int_fast32_t numBits, offset;
				CProb *probLen = prob + LZMA_LEN_CHOICE;
				IfBit0(probLen) {
					UpdateBit0(probLen);
					probLen = prob + LZMA_LEN_LOW
					          + (posState
					             << LZMA_LEN_NUM_LOW_BITS);
					offset = 0;
					numBits = LZMA_LEN_NUM_LOW_BITS;
				}
				else {
					UpdateBit1(probLen);
					probLen = prob + LZMA_LEN_CHOICE2;
					IfBit0(probLen) {
						UpdateBit0(probLen);
						probLen = prob + LZMA_LEN_MID
						          + (posState
						             << LZMA_LEN_NUM_MID_BITS);
						offset = LZMA_LEN_NUM_LOW_SYMBOLS;
						numBits = LZMA_LEN_NUM_MID_BITS;
					}
					else {
						UpdateBit1(probLen);
						probLen = prob + LZMA_LEN_HIGH;
						offset = LZMA_LEN_NUM_LOW_SYMBOLS
						         + LZMA_LEN_NUM_MID_SYMBOLS;
						numBits = LZMA_LEN_NUM_HIGH_BITS;
					}
				}
				RangeDecoderBitTreeDecode(probLen, numBits, len);
				len += offset;
			}

			if (state < 4) {
				int_fast32_t posSlot;
				state += LZMA_NUM_LIT_STATES;
				prob = p + LZMA_POS_SLOT + (MIN (len,
				                                 LZMA_NUM_LEN_TO_POS_STATES - 1)
				                            << LZMA_NUM_POS_SLOT_BITS);
				RangeDecoderBitTreeDecode(prob, LZMA_NUM_POS_SLOT_BITS, posSlot);
				if (posSlot >= LZMA_START_POS_MODEL_INDEX) {
					int_fast32_t numDirectBits = ((posSlot >> 1) - 1);
					rep0 = (2 | ((uint32_t)posSlot & 1));
					if (posSlot < LZMA_END_POS_MODEL_INDEX) {
						rep0 <<= numDirectBits;
						prob = p + LZMA_SPEC_POS + rep0 - posSlot - 1;
					} else {
						numDirectBits -= LZMA_NUM_ALIGN_BITS;
						do {
							RC_NORMALIZE
							range >>= 1;
							rep0 <<= 1;
							if (code >= range) {
								code -= range;
								rep0 |= 1;
							}
						} while (--numDirectBits != 0);
						prob = p + LZMA_ALIGN;
						rep0 <<= LZMA_NUM_ALIGN_BITS;
						numDirectBits = LZMA_NUM_ALIGN_BITS;
					}
					{
						int_fast32_t mi = 1;
						i = 1;
						do {
							CProb *prob3 = prob + mi;
							RC_GET_BIT2(prob3, mi, ; , rep0 |= i);
							i <<= 1;
						} while(--numDirectBits != 0);
					}
				} else {
					rep0 = posSlot;
				}
				if (++rep0 == (uint32_t)(0)) {
					/* End of stream marker detected */
					STATE->status = LZMADEC_STATUS_STREAM_END;
					break;
				}
			}

			if (rep0 > distance_limit)
				return LZMADEC_DATA_ERROR;

			len += LZMA_MATCH_MIN_LEN;
			if (dictionary_size - distance_limit > (uint32_t)(len))
				distance_limit += len;
			else
				distance_limit = dictionary_size;
		}
	}
	RC_NORMALIZE;

	if (STATE->uncompressed_size < total_out) {
		STATE->status = LZMADEC_STATUS_ERROR;
		return LZMADEC_DATA_ERROR;
	}

	/* Store the saved values back to the lzmadec_stream structure. */
	strm->total_in += (strm->avail_in - avail_in);
	strm->total_out = total_out;
	strm->avail_in = avail_in;
	strm->avail_out -= (next_out - strm->next_out);
	strm->next_in = next_in;
	strm->next_out = next_out;
	STATE->range = range;
	STATE->code = code;
	STATE->rep0 = rep0;
	STATE->rep1 = rep1;
	STATE->rep2 = rep2;
	STATE->rep3 = rep3;
	STATE->state = state;
	STATE->len = len;
	STATE->dictionary_position = dictionary_position;
	STATE->distance_limit = distance_limit;
	STATE->buffer_size = buffer_size;
	STATE->buffer_position = buffer;

	if (STATE->status == LZMADEC_STATUS_STREAM_END
	        || STATE->uncompressed_size == total_out) {
		STATE->status = LZMADEC_STATUS_STREAM_END;
		if (len == 0)
			return LZMADEC_STREAM_END;
	}
	return LZMADEC_OK;
}

#include <fcntl.h>

#define CHUNKSIZE_IN 4096
#define CHUNKSIZE_OUT (1024*512)

int lzmadec(char *input, char *output){
	int ret;
	lzmadec_stream strm;
	size_t write_size;
	FILE *file_in = fopen(input,"rb");
	FILE *file_out = fopen(output,"wb");
	unsigned char *buffer_in = (unsigned char *)malloc(CHUNKSIZE_IN);
	unsigned char *buffer_out = (unsigned char *)malloc(CHUNKSIZE_OUT);
	strm.lzma_alloc = NULL;
	strm.lzma_free = NULL;
	strm.opaque = NULL;
	strm.avail_in = 0;
	strm.next_in = NULL;
	lzmadec_init (&strm);
	while (1) {
		if (strm.avail_in == 0) {
			strm.next_in = buffer_in;
			strm.avail_in = fread (buffer_in, sizeof (unsigned char), CHUNKSIZE_IN, file_in);
		}
		strm.next_out = buffer_out;
		strm.avail_out = CHUNKSIZE_OUT;
		ret = lzmadec_decode (&strm, strm.avail_in == 0);
		if (ret != LZMADEC_OK && ret != LZMADEC_STREAM_END){
			fclose(file_in);
			fclose(file_out);
			return 1;
		}
		write_size = CHUNKSIZE_OUT - strm.avail_out;
		if (write_size != (fwrite (buffer_out, sizeof (unsigned char),write_size, file_out))){
			fclose(file_in);
			fclose(file_out);
			return 2;
		}
		if (ret == LZMADEC_STREAM_END) {
			lzmadec_end (&strm);
			fclose(file_in);
			fclose(file_out);
			return 0;
		}
	}
	fclose(file_in);
	fclose(file_out);
	return 0;
}
