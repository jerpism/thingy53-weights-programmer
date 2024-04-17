#ifndef HEADER.H_H__
#define HEADER.H_H__
const _Float16 *normalization_kweights = (_Float16*)(FLASH_BASE + 0);
const _Float16 *normalization_bweights = NULL;
const size_t normalization_kshape[] = {  3, 0  };
const size_t normalization_bshape[] = {  0  };

const _Float16 *conv2d_kweights = (_Float16*)(FLASH_BASE + 0x8);
const _Float16 *conv2d_bweights = (_Float16*)(FLASH_BASE + 0x248);
const size_t conv2d_kshape[] = {  3, 3, 1, 32, 0  };
const size_t conv2d_bshape[] = {  32, 0  };

const _Float16 *conv2d_1_kweights = (_Float16*)(FLASH_BASE + 0x288);
const _Float16 *conv2d_1_bweights = (_Float16*)(FLASH_BASE + 0x9288);
const size_t conv2d_1_kshape[] = {  3, 3, 32, 64, 0  };
const size_t conv2d_1_bshape[] = {  64, 0  };

const _Float16 *dense_kweights = (_Float16*)(FLASH_BASE + 0x9308);
const _Float16 *dense_bweights = (_Float16*)(FLASH_BASE + 0x191308);
const size_t dense_kshape[] = {  12544, 64, 0  };
const size_t dense_bshape[] = {  64, 0  };

const _Float16 *dense_1_kweights = (_Float16*)(FLASH_BASE + 0x191388);
const _Float16 *dense_1_bweights = (_Float16*)(FLASH_BASE + 0x191788);
const size_t dense_1_kshape[] = {  64, 8, 0  };
const size_t dense_1_bshape[] = {  8, 0  };

#endif /* HEADER.H_H__ */