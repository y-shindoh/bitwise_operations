/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	bitwise_operations.hpp
 * @brief	ビット演算関係の関数群
 * @author	Yasutaka SHINDOH / 新堂 安孝
 */

#ifndef	__BITWISE_OPERATIONS_HPP__
#define	__BITWISE_OPERATIONS_HPP__	"bitwise_operations.hpp"

#include <cstddef>
#include <cstdio>
#include <cassert>

namespace ys
{
	/**
	 * ビット演算関係の関数群のクラス
	 * @note	テンプレートの型 @a TYPE には、 @a int より大きな符号なし整数を指定する。
	 */
	template<typename TYPE>
	class BitwiseOperation
	{
	private:

		/**
		 * ビット演算処理で内部的に用いる符号なし整数
		 */
		typedef unsigned long long int bo_uint;

	public:

		/**
		 * ビットの状況を出力
		 * @param[out]	file	出力先ファイル
		 * @param[in]	bits	処理対象の整数
		 */
		static void
		print(FILE* file,
			  TYPE bits)
			{
				size_t h, k;
				int c;

				for (size_t i(0); i < sizeof(TYPE); ++i) {
					if (0 < i) std::fputc((int)' ', file);
#ifdef	__LITTLE_ENDIAN__
					h = sizeof(TYPE) - i - 1;
#else	// __LITTLE_ENDIAN__
					h = i;
#endif	// __LITTLE_ENDIAN__
					for (size_t j(0); j < 8; ++j) {
						k = 8 - j - 1;
						c = (int)'0';
						if (bits & ((TYPE)1 << (h * 8 + k))) c = (int)'1';
						std::fputc(c, file);
					}
				}

				std::fprintf(file, " [0x%lX]\n", (size_t)bits);
			}

		/**
		 * 指定位置のビットを取得
		 * @param[in]	bits	処理対象の整数
		 * @param[in]	i	位置
		 * @return	処理後の整数
		 */
		static TYPE
		get(TYPE bits,
			size_t i)
			{
				assert(i < sizeof(TYPE) * 8);

				return bits & ((TYPE)1 << i);
			}

		/**
		 * 指定位置以下の全ビットを取得
		 * @param[in]	bits	処理対象の整数
		 * @param[in]	i	位置
		 * @return	処理後の整数
		 */
		static TYPE
		get_lower(TYPE bits,
				  size_t i)
			{
				assert(i < sizeof(TYPE) * 8);

				return bits & ~(~(TYPE)0 << i + 1);
			}

		/**
		 * 指定位置以上の全ビットを取得
		 * @param[in]	bits	処理対象の整数
		 * @param[in]	i	位置
		 * @return	処理後の整数
		 */
		static TYPE
		get_higher(TYPE bits,
				   size_t i)
			{
				assert(i < sizeof(TYPE) * 8);

				return bits & ~(((TYPE)1 << i) - (TYPE)1);
			}

		/**
		 * 指定位置のビットを1にする
		 * @param[in]	bits	処理対象の整数
		 * @param[in]	i	位置
		 * @return	処理後の整数
		 */
		static TYPE
		set(TYPE bits,
			size_t i)
			{
				assert(i < sizeof(TYPE) * 8);

				return bits | ((TYPE)1 << i);
			}

		/**
		 * 指定位置以下の全ビットを1にする
		 * @param[in]	bits	処理対象の整数
		 * @param[in]	i	位置
		 * @return	処理後の整数
		 */
		static TYPE
		set_lower(TYPE bits,
				  size_t i)
			{
				assert(i < sizeof(TYPE) * 8);

				return bits | ~(~(TYPE)0 << i + 1);
			}

		/**
		 * 指定位置以上の全ビットを1にする
		 * @param[in]	bits	処理対象の整数
		 * @param[in]	i	位置
		 * @return	処理後の整数
		 */
		static TYPE
		set_higher(TYPE bits,
				   size_t i)
			{
				assert(i < sizeof(TYPE) * 8);

				return bits | ~(TYPE)0 << i;
			}

		/**
		 * 指定位置のビットを0にする
		 * @param[in]	bits	処理対象の整数
		 * @param[in]	i	位置
		 * @return	処理後の整数
		 */
		static TYPE
		clear(TYPE bits,
			  size_t i)
			{
				assert(i < sizeof(TYPE) * 8);

				return bits & ~((TYPE)1 << i);
			}

		/**
		 * 指定位置以下の全ビットを0にする
		 * @param[in]	bits	処理対象の整数
		 * @param[in]	i	位置
		 * @return	処理後の整数
		 */
		static TYPE
		clear_lower(TYPE bits,
					size_t i)
			{
				assert(i < sizeof(TYPE) * 8);

				return bits & (~(TYPE)0 << i + 1);
			}

		/**
		 * 指定位置以上の全ビットを0にする
		 * @param[in]	bits	処理対象の整数
		 * @param[in]	i	位置
		 * @return	処理後の整数
		 */
		static TYPE
		clear_higher(TYPE bits,
					 size_t i)
			{
				assert(i < sizeof(TYPE) * 8);

				return bits & ~(~(TYPE)0 << i);
			}

		/**
		 * 最も低い桁の1のビットを取得
		 * @param[in]	bits	処理対象の整数
		 * @return	処理後の整数
		 */
		static TYPE
		get_lowest_1(TYPE bits)
			{
				return bits & (~bits + (TYPE)1);
			}

		/**
		 * 最も高い桁の1のビットを取得
		 * @param[in]	bits	処理対象の整数
		 * @return	処理後の整数
		 */
		static TYPE
		get_highest_1(TYPE bits)
			{
				bo_uint v = (bo_uint)bits;

				v = ((bo_uint)0xFFFFFFFF00000000 & v) ? ((bo_uint)0xFFFFFFFF00000000 & v) : v;
				v = ((bo_uint)0xFFFF0000FFFF0000 & v) ? ((bo_uint)0xFFFF0000FFFF0000 & v) : v;
				v = ((bo_uint)0xFF00FF00FF00FF00 & v) ? ((bo_uint)0xFF00FF00FF00FF00 & v) : v;
				v = ((bo_uint)0xF0F0F0F0F0F0F0F0 & v) ? ((bo_uint)0xF0F0F0F0F0F0F0F0 & v) : v;
				v = ((bo_uint)0xCCCCCCCCCCCCCCCC & v) ? ((bo_uint)0xCCCCCCCCCCCCCCCC & v) : v;
				v = ((bo_uint)0xAAAAAAAAAAAAAAAA & v) ? ((bo_uint)0xAAAAAAAAAAAAAAAA & v) : v;

				return (TYPE)v;
			}

		/**
		 * 1のビットの総数を算出
		 * @param[in]	bits	処理対象の整数
		 * @return	1のビットの総数
		 */
		static size_t
		count_1(TYPE bits)
			{
				bo_uint v = (bo_uint)bits;

				v = (((bo_uint)0xAAAAAAAAAAAAAAAA & v) >> 1) + ((bo_uint)0x5555555555555555 & v);
				v = (((bo_uint)0xCCCCCCCCCCCCCCCC & v) >> 2) + ((bo_uint)0x3333333333333333 & v);
				v = (((bo_uint)0xF0F0F0F0F0F0F0F0 & v) >> 4) + ((bo_uint)0x0F0F0F0F0F0F0F0F & v);
				v = (((bo_uint)0xFF00FF00FF00FF00 & v) >> 8) + ((bo_uint)0x00FF00FF00FF00FF & v);
				v = (((bo_uint)0xFFFF0000FFFF0000 & v) >> 16) + ((bo_uint)0x0000FFFF0000FFFF & v);
				v = (((bo_uint)0xFFFFFFFF00000000 & v) >> 32) + ((bo_uint)0x00000000FFFFFFFF & v);

				return (size_t)v;
			}

		/**
		 * 1のビットの総数が等しい次に小さな整数を算出
		 * @param[in]	bits	処理対象の整数
		 * @return	1のビットの総数が等しい次に小さな整数
		 * @note	算出失敗時は引数 @a bit がそのまま返却される。
		 * @todo	アルゴリズムの説明を追記する。
		 */
		static TYPE
		previous_same_1_count(TYPE bits)
			{
				bool t;
				size_t c[2] = {0, 0};

				for (size_t i(0); i < sizeof(TYPE) * 8 - 1; ++i) {
					t = (bool)(bits & ((TYPE)1 << i));
					if (t || !(bits & ((TYPE)1 << i + 1))) {
						c[(size_t)t]++;
						continue;
					}
					return bits - ((TYPE)1 << c[1]) - ((TYPE)1 << c[0]) + (TYPE)1;
				}

				return bits;
			}

		/**
		 * 1のビットの総数が等しい次に大きな整数を算出
		 * @param[in]	bits	処理対象の整数
		 * @return	1のビットの総数が等しい次に大きな整数
		 * @note	算出失敗時は引数 @a bit がそのまま返却される。
		 * @todo	アルゴリズムの説明を追記する。
		 */
		static TYPE
		next_same_1_count(TYPE bits)
			{
				bool t;
				size_t c[2] = {0, 0};

				for (size_t i(0); i < sizeof(TYPE) * 8 - 1; ++i) {
					t = (bool)(bits & ((TYPE)1 << i));
					if (!t || (bits & ((TYPE)1 << i + 1))) {
						c[(size_t)t]++;
						continue;
					}
					return bits + ((TYPE)1 << c[0]) + ((TYPE)1 << c[1]) - (TYPE)1;
				}

				return bits;
			}
	};
};

#endif	// __BITWISE_OPERATIONS_HPP__
