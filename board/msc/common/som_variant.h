#ifndef SOM_VARIANT_H
#define SOM_VARIANT_H

/*
 * Copyright (C) 2022 Avnet Embedded
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

typedef struct revision_record {
	const char *			revision_tag;
	uint32_t				dram_size[2];
} revision_record_t;

typedef struct variant_record {
	const char *			feature_tag;
	revision_record_t 		revisions[10];
} variant_record_t;

#define REVISION_RECORD(REVISION, DRAM_SIZE0, DRAM_SIZE1) \
		{ \
			.revision_tag	= REVISION, \
			.dram_size		= { DRAM_SIZE0, DRAM_SIZE1 } \
		}

#define FEATURE_RECORD(FEATURE, ...) \
		{ \
			.feature_tag	= FEATURE, \
			.revisions	= { \
					__VA_ARGS__ \
			}, \
		}

const revision_record_t *find_revision_record(variant_record_t *variants,
		const char *feature, const char *revision);

void print_variants(variant_record_t *variants);

#endif /* SOM_VARIANT_H */
