// Author: Ivan Kazmenko (gassa@mail.ru)
#include <cassert>
#include "combinatorial_object.h"

void CombinatorialObject::check (int n)
{
	auto all = generate_all (n);
	assert ((int64_t) (all.size ()) == total (n));
	for (size_t i = 0; i != all.size (); i++)
	{
		assert ((int) (all[i].size ()) == n);
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
	std::string cmd;
	while (in_stream >> cmd)
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
		else
		{
			out_stream << "unknown command: " << cmd << std::endl;
		}
	}
}

int main (void)
{
	CombinatorialObject * calculator = getCombinatorialObject ();
	calculator -> interact ();
	return 0;
}
