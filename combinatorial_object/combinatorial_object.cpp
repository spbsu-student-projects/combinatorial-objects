// Author: Ivan Kazmenko (gassa@mail.ru)
#include <cassert>
#include <string>
#include "combinatorial_object.h"

void CombinatorialObject::check (int n)
{
	auto all = generate_all (n);
	assert ((int64_t) (all.size ()) == total (n));
	for (size_t i = 0; i != all.size (); i++)
	{
		assert ((int) (all[i].size ()) == n);
		assert (is_valid (all[i]));
		if (i > 0)
		{
			assert (all[i - 1] < all[i]);
		}
		assert (all[i] == object_by_number (n, i));
		assert ((int64_t) (i) == number_by_object (all[i]));
		auto u = all[i];
		assert (prev (u) == (i != 0));
		assert (i == 0 || u == all[i - 1]);
		auto v = all[i];
		assert (next (v) == (i + 1 != all.size ()));
		assert (i + 1 == all.size () || v == all[i + 1]);
	}

	if (total (n) > 0)
	{
		auto u = object_by_number (n, 0);
		int64_t n_check_1 = 0;
		do
		{
			assert (is_valid (u));
			n_check_1 += 1;
		}
		while (next (u));
		assert (n_check_1 == total (n));

		auto v = object_by_number (n, total (n) - 1);
		int64_t n_check_2 = 0;
		do
		{
			assert (is_valid (v));
			n_check_2 += 1;
		}
		while (prev (v));
		assert (n_check_2 == total (n));
	}
}

vector <int> CombinatorialObject::input (int n, istream & in_stream)
{
	vector <int> res (n);
	for (size_t i = 0; i != res.size (); i++)
	{
		in_stream >> res[i];
	}
	return res;
}

void CombinatorialObject::print (vector <int> const & v, ostream & out_stream)
{
	for (size_t i = 0; i != v.size (); i++)
	{
		out_stream << v[i];
		if (i + 1 != v.size ())
		{
			out_stream << " ";
		}
	}
	out_stream << std::endl;
}

void CombinatorialObject::interact (istream & in_stream, ostream & out_stream)
{
	out_stream << name () << " calculator" << std::endl;
	out_stream << "enter command `help` to list commands" << std::endl;
	std::string cmd;
	while (out_stream << ">", in_stream >> cmd)
	{
		if (cmd == "exit")
		{
			break;
		}
		else if (cmd == "check")
		{
			int n;
			in_stream >> n;
			check (n);
		}
		else if (cmd == "total")
		{
			int n;
			in_stream >> n;
			out_stream << total (n) << std::endl;
		}
		else if (cmd == "generate_all" || cmd == "generate")
		{
			int n;
			in_stream >> n;
			auto res = generate_all (n);
			for (auto v : res)
			{
				print (v, out_stream);
			}
		}
		else if (cmd == "is_valid" || cmd == "valid")
		{
			int n;
			in_stream >> n;
			auto v = input (n, in_stream);
			out_stream << is_valid (v) << std::endl;
		}
		else if (cmd == "number_by_object" || cmd == "number")
		{
			int n;
			in_stream >> n;
			auto v = input (n, in_stream);
			out_stream << number_by_object (v) << std::endl;
		}
		else if (cmd == "object_by_number" || cmd == "object")
		{
			int n;
			int64_t k;
			in_stream >> n >> k;
			print (object_by_number (n, k), out_stream);
		}
		else if (cmd == "prev")
		{
			int n;
			in_stream >> n;
			auto v = input (n, in_stream);
			auto success = prev (v);
			print (v, out_stream);
			out_stream << success << std::endl;
		}
		else if (cmd == "next")
		{
			int n;
			in_stream >> n;
			auto v = input (n, in_stream);
			auto success = next (v);
			print (v, out_stream);
			out_stream << success << std::endl;
		}
		else if (cmd == "help")
		{
			out_stream << "commands:" << std::endl;
			out_stream << "  help:                              ";
			out_stream << "show this help" << std::endl;
			out_stream << "  exit:                              ";
			out_stream << "exit the program" << std::endl;
			out_stream << "  check n:                           ";
			out_stream << "perform checks for all objects of size n" << std::endl;
			out_stream << "  total n:                           ";
			out_stream << "number of objects of size n" << std::endl;
			out_stream << "  generate[_all] n:                  ";
			out_stream << "list all objects of size n, one per line" << std::endl;
			out_stream << "  [is_]valid n v1 v2 ... vn:         ";
			out_stream << "check validity of object v" << std::endl;
			out_stream << "  number[_by_object] n v1 v2 ... vn: ";
			out_stream << "0-based number of object v of size n" << std::endl;
			out_stream << "  object[_by_number] n k:            ";
			out_stream << "object of size n with 0-based number k" << std::endl;
			out_stream << "  prev n v1 v2 ... vn:               ";
			out_stream << "make previous object, check if was first" << std::endl;
			out_stream << "  next n v1 v2 ... vn:               ";
			out_stream << "make next object, check if was last" << std::endl;
		}
		else
		{
			out_stream << "unknown command: " << cmd << std::endl;
		}
	}
}

CombinatorialObject::~CombinatorialObject ()
{
}
