/*
 * ===============================================================
 *    Description:  db::property implementation.
 *
 *        Created:  2014-05-30 17:24:08
 *
 *         Author:  Ayush Dubey, dubey@cs.cornell.edu
 *
 * Copyright (C) 2013, Cornell University, see the LICENSE file
 *                     for licensing agreement
 * ===============================================================
 */

#include "db/property.h"

using db::property;
using db::property_key_hasher;

property :: property()
{ }

property :: property(const std::string &k, const std::string &v)
    : node_prog::property(k, v)
{ }

property :: property(const std::string &k, const std::string &v, const vclock_ptr_t &creat)
    : node_prog::property(k, v)
    , creat_time(creat)
{ }

property :: property(const property &other)
    : node_prog::property(other.key, other.value)
    , creat_time(other.creat_time)
{
    if (other.del_time) {
        del_time = other.del_time;
    }
}

bool
property :: operator==(property const &other) const
{
    return (key == other.key) && (value == other.value);
}

const vclock_ptr_t&
property :: get_creat_time() const
{
    return creat_time;
}

const vclock_ptr_t&
property :: get_del_time() const
{
    return del_time;
}

bool
property :: is_deleted() const
{
    return (del_time != nullptr);
}

void
property :: update_del_time(const vclock_ptr_t &tdel)
{
    del_time = tdel;
}

void
property :: update_creat_time(const vclock_ptr_t &tcreat)
{
    creat_time = tcreat;
}

size_t
property_key_hasher :: operator()(const property &p) const
{
    return weaver_util::murmur_hasher<std::string>()(p.key);
}
