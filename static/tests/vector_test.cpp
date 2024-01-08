#include "catch.hpp"
#include "vector.h"

TEST_CASE("Vector Initialization and Capacity", "Vector") {
    SECTION("Default constructor creates an empty vector") {
        tmp::Vector<int> v;
        REQUIRE(v.get_size() == 0);
        REQUIRE(v.get_capacity() == 0);
        REQUIRE(v.empty());
    }

    SECTION("Vector with specified size is correctly initialized") {
        tmp::Vector<int> v(5);
        REQUIRE(v.get_size() == 5);
        REQUIRE(v.get_capacity() == 5);
        REQUIRE_FALSE(v.empty());
    }

    SECTION("Vector with specified size and value is correctly initialized") {
        tmp::Vector<int> v(3, 42);
        REQUIRE(v.get_size() == 3);
        REQUIRE(v.get_capacity() == 3);
        REQUIRE_FALSE(v.empty());
        for (const auto& elem : v) {
            REQUIRE(elem == 42);
        }
    }

    SECTION("Vector constructed from initializer list is initialized correctly") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};
        REQUIRE(v.get_size() == 5);
        REQUIRE(v.get_capacity() == 5);
        REQUIRE_FALSE(v.empty());
        for (size_t i = 0; i < v.get_size(); ++i) {
            REQUIRE(v[i] == static_cast<int>(i + 1));
        }
    }
}

TEST_CASE("Insertion and Deletion", "Vector") {
    SECTION("Inserting elements at specific positions") {
        tmp::Vector<int> v = {1, 2, 4, 5};
        auto it = v.insert(v.begin() + 2, 3);
        REQUIRE(*it == 3);
        REQUIRE(v == tmp::Vector<int>{1, 2, 3, 4, 5});
    }

    SECTION("Erasing elements from specific positions") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};
        auto it = v.erase(v.begin() + 2);
        REQUIRE(*it == 4);
        REQUIRE(v == tmp::Vector<int>{1, 2, 4, 5});
    }
}

TEST_CASE("Element Access", "Vector") {
    SECTION("Accessing elements using [] operator") {
        tmp::Vector<int> v = {10, 20, 30};
        REQUIRE(v[0] == 10);
        REQUIRE(v[1] == 20);
        REQUIRE(v[2] == 30);
    }

    SECTION("Accessing elements using at() method with valid indices") {
        tmp::Vector<int> v = {10, 20, 30};
        REQUIRE(v.at(0) == 10);
        REQUIRE(v.at(1) == 20);
        REQUIRE(v.at(2) == 30);
    }

    SECTION("Accessing elements using at() method with out-of-range indices") {
        tmp::Vector<int> v = {10, 20, 30};
        REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
    }

    SECTION("Accessing first and last elements") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};
        REQUIRE(v.front() == 1);
        REQUIRE(v.back() == 5);
    }

    SECTION("Accessing vector data") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};
        auto data = v.data();
        REQUIRE(data[2] == 3);
    }
}

TEST_CASE("Modification Operations", "Vector") {
    SECTION("Pushing elements into the vector") {
        tmp::Vector<int> v;
        v.push_back(100);
        v.push_back(200);
        REQUIRE(v.get_size() == 2);
        REQUIRE(v[0] == 100);
        REQUIRE(v[1] == 200);
    }

    SECTION("Popping elements from the vector") {
        tmp::Vector<int> v = {10, 20, 30};
        v.pop_back();
        REQUIRE(v.get_size() == 2);
        REQUIRE(v[0] == 10);
        REQUIRE(v[1] == 20);
    }
}

TEST_CASE("Iteration", "Vector") {
    SECTION("Iterating through elements using iterators") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};
        int count = 1;
        for (const auto& elem : v) {
            REQUIRE(elem == count++);
        }
    }
}

TEST_CASE("Capacity Management", "Vector") {
    SECTION("Reserving additional capacity") {
        tmp::Vector<int> v;
        v.reserve(10);
        REQUIRE(v.get_capacity() >= 10);
    }

    SECTION("Shrinking vector capacity") {
        tmp::Vector<int> v = {1, 2, 3};
        v.shrink_to_fit();
        REQUIRE(v.get_capacity() == v.get_size());
    }
}

TEST_CASE("Resizing", "Vector") {
    SECTION("Increasing vector size") {
        tmp::Vector<int> v = {1, 2, 3};
        v.resize(5);
        REQUIRE(v.get_size() == 5);
    }

    SECTION("Decreasing vector size") {
        tmp::Vector<int> v = {1, 2, 3};
        v.resize(1);
        REQUIRE(v.get_size() == 1);
        REQUIRE(v[0] == 1);
    }
}

TEST_CASE("Clear and Assignment", "Vector") {
    SECTION("Clearing the vector") {
        tmp::Vector<int> v = {1, 2, 3};
        v.clear();
        REQUIRE(v.get_size() == 0);
        REQUIRE(v.empty());
    }

    SECTION("Assigning values using assignment operator") {
        tmp::Vector<int> v1 = {1, 2, 3};
        tmp::Vector<int> v2;
        v2 = v1;
        REQUIRE(v2 == v1);
    }
}

TEST_CASE("Erase Method", "Vector") {
    SECTION("Erasing elements at specific positions") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};

        auto it = v.erase(v.begin() + 2);
        REQUIRE(*it == 4);
        REQUIRE(v == tmp::Vector<int>{1, 2, 4, 5});
        REQUIRE(v.get_size() == 4);
        REQUIRE(v.get_capacity() == 5);
    }

    SECTION("Erasing elements from both ends") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};

        v.erase(v.begin());
        v.erase(v.end() - 1);

        REQUIRE(v == tmp::Vector<int>{2, 3, 4});
        REQUIRE(v.get_size() == 3);
        REQUIRE(v.get_capacity() == 5);
    }

    SECTION("Erasing elements to deallocate") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        v.erase(v.begin());
        v.erase(v.begin());
        v.erase(v.begin());
        v.erase(v.begin());
        v.erase(v.begin());

        REQUIRE(v.get_size() == 4);
        REQUIRE(v.get_capacity() == 4);
    }
}

TEST_CASE("Comparator Methods with Iterators", "Vector") {
    SECTION("Equality comparison between iterators") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};

        auto it1 = v.begin();
        auto it2 = v.begin();
        auto it3 = v.end();

        REQUIRE(it1 == it2);
        REQUIRE_FALSE(it1 == it3);
    }

    SECTION("Inequality comparison between iterators") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};

        auto it1 = v.begin();
        auto it2 = v.begin();
        auto it3 = v.end();

        REQUIRE_FALSE(it1 != it2);
        REQUIRE(it1 != it3);
    }

    SECTION("Comparison of iterator positions") {
        tmp::Vector<int> v = {1, 2, 3, 4, 5};

        auto it1 = v.begin();
        auto it2 = v.begin() + 2;
        auto it3 = v.end();

        REQUIRE(it1 < it2);
        REQUIRE(it1 <= it2);
        REQUIRE_FALSE(it2 < it1);
        REQUIRE(it3 > it2);
        REQUIRE(it3 >= it2);
        REQUIRE_FALSE(it2 > it3);

    }
}

TEST_CASE("Copy and Move Constructors", "Vector") {
    SECTION("Copy Constructor") {
        tmp::Vector<int> original = {1, 2, 3, 4, 5};
        tmp::Vector<int> copied(original);

        REQUIRE(original == copied);
        REQUIRE(original.get_size() == copied.get_size());
        REQUIRE(original.get_capacity() == copied.get_capacity());
        REQUIRE(original.data() != copied.data());
    }

    SECTION("Move Constructor") {
        tmp::Vector<int> original = {1, 2, 3, 4, 5};
        tmp::Vector<int> moved(std::move(original));

        REQUIRE(moved.get_size() == 5);
        REQUIRE(moved.get_capacity() == 5);
        REQUIRE(original.get_size() == 0);
        REQUIRE(original.get_capacity() == 0);
        REQUIRE(moved[0] == 1);
    }

}


