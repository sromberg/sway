/*
Copyright (c) 2011, Andrea Sansottera
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 - Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
 - Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <boost/test/unit_test.hpp>

#include <sway/bounded_priority_queue.hpp>

using namespace sway;

BOOST_AUTO_TEST_CASE(TestBPQ) {

	bounded_priority_queue<int> bpq(2);

	BOOST_REQUIRE_EQUAL(bpq.size(), 0u);
	
	bpq.push(10);
	BOOST_REQUIRE_EQUAL(bpq.size(), 1u);
	BOOST_CHECK_EQUAL(bpq.top(), 10);

	bpq.push(5);
	BOOST_REQUIRE_EQUAL(bpq.size(), 2u);
	BOOST_CHECK_EQUAL(bpq.top(), 5);

	bpq.push(8);
	BOOST_REQUIRE_EQUAL(bpq.size(), 2u);
	BOOST_CHECK_EQUAL(bpq.top(), 5);

	bpq.pop_top();

	BOOST_REQUIRE_EQUAL(bpq.size(), 1u);
	BOOST_CHECK_EQUAL(bpq.top(), 8);

	bpq.push(3);
	
	BOOST_REQUIRE_EQUAL(bpq.size(), 2u);
	BOOST_CHECK_EQUAL(bpq.bottom(), 8);
}

BOOST_AUTO_TEST_CASE(TestBPQ2) {

	bounded_priority_queue<int> bpq(3);

	BOOST_REQUIRE_EQUAL(bpq.size(), 0u);

	bpq.push(1); // 1
	bpq.push(3); // 1 3
	bpq.push(2); // 1 2 3
	bpq.push(4); // 1 2 3
	bpq.push(0); // 0 1 2

	BOOST_REQUIRE_EQUAL(bpq.size(), 3u);
	BOOST_CHECK_EQUAL(bpq.top(), 0);
	BOOST_CHECK_EQUAL(bpq.bottom(), 2);

	bpq.push(5);

	BOOST_REQUIRE_EQUAL(bpq.size(), 3u);
	BOOST_CHECK_EQUAL(bpq.top(), 0);
	BOOST_CHECK_EQUAL(bpq.bottom(), 2);
}

BOOST_AUTO_TEST_CASE(TestBPQSmall) {

	bounded_priority_queue<int> bpq(2);

	bpq.push(1);
	bpq.push(3);
	bpq.push(2);

	BOOST_REQUIRE_EQUAL(bpq.size(), 2u);
	BOOST_CHECK_EQUAL(bpq.top(), 1);
	BOOST_CHECK_EQUAL(bpq.bottom(), 2);
}

BOOST_AUTO_TEST_CASE(TestBPQConstructFromVector) {

	std::vector<int> data;
	data.push_back(10);
	data.push_back(11);
	data.push_back(5);
	data.push_back(9);

	bounded_priority_queue<int> bpq(data);

	BOOST_REQUIRE_EQUAL(bpq.size(), 4u);
	BOOST_REQUIRE_EQUAL(bpq.max_size(), 4u);
	BOOST_CHECK_EQUAL(bpq.top(), 5);
	BOOST_CHECK_EQUAL(bpq.bottom(), 11);
}

BOOST_AUTO_TEST_CASE(TestBPQConstructFromLargerVector) {

	std::vector<int> data;
	data.push_back(10);
	data.push_back(11);
	data.push_back(5);
	data.push_back(9);

	bounded_priority_queue<int> bpq(3, data);

	BOOST_REQUIRE_EQUAL(bpq.size(), 3u);
	BOOST_REQUIRE_EQUAL(bpq.max_size(), 3u);
	BOOST_CHECK_EQUAL(bpq.top(), 5);
	BOOST_CHECK_EQUAL(bpq.bottom(), 10);
}

BOOST_AUTO_TEST_CASE(TestBPQConstructFromSmallerVector) {

	std::vector<int> data;
	data.push_back(10);
	data.push_back(11);
	data.push_back(5);
	data.push_back(9);

	bounded_priority_queue<int> bpq(10, data);

	BOOST_REQUIRE_EQUAL(bpq.size(), 4u);
	BOOST_REQUIRE_EQUAL(bpq.max_size(), 10u);
	BOOST_CHECK_EQUAL(bpq.top(), 5);
	BOOST_CHECK_EQUAL(bpq.bottom(), 11);
}
