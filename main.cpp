/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	main.cpp
 * @brief	bitwise_operations.hppの動作確認用コマンド
 * @author	Yasutaka SHINDOH / 新堂 安孝
 */

#include <cstdio>
#include "bitwise_operations.hpp"

int main()
{
	unsigned int x(0xFDB86420u);
	unsigned int y;

	ys::BitwiseOperation<unsigned int>::print(stdout, x);

	y = ys::BitwiseOperation<unsigned int>::get(x, 24);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = ys::BitwiseOperation<unsigned int>::set(x, 3);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = ys::BitwiseOperation<unsigned int>::set_lower(x, 3);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = ys::BitwiseOperation<unsigned int>::set_higher(x, 3);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = ys::BitwiseOperation<unsigned int>::clear(x, 24);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = ys::BitwiseOperation<unsigned int>::clear_lower(x, 20);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = ys::BitwiseOperation<unsigned int>::clear_higher(x, 20);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = ys::BitwiseOperation<unsigned int>::get_lowest_1(x);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = ys::BitwiseOperation<unsigned int>::get_highest_1(x);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = (unsigned int)ys::BitwiseOperation<unsigned int>::count_1(x);
	std::printf("%u\n", y);

	y = ys::BitwiseOperation<unsigned int>::previous_same_1_count(x);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	y = ys::BitwiseOperation<unsigned int>::next_same_1_count(x);
	ys::BitwiseOperation<unsigned int>::print(stdout, y);

	return 0;
}
