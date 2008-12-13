/*
 *
 *  Connection Manager
 *
 *  Copyright (C) 2007-2008  Intel Corporation. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "connman.h"

static GSList *resolver_list = NULL;

static gint compare_priority(gconstpointer a, gconstpointer b)
{
	const struct connman_resolver *resolver1 = a;
	const struct connman_resolver *resolver2 = b;

	return resolver2->priority - resolver1->priority;
}

/**
 * connman_resolver_register:
 * @resolver: resolver module
 *
 * Register a new resolver module
 *
 * Returns: %0 on success
 */
int connman_resolver_register(struct connman_resolver *resolver)
{
	DBG("resolver %p name %s", resolver, resolver->name);

	resolver_list = g_slist_insert_sorted(resolver_list, resolver,
							compare_priority);

	return 0;
}

/**
 * connman_resolver_unregister:
 * @resolver: resolver module
 *
 * Remove a previously registered resolver module
 */
void connman_resolver_unregister(struct connman_resolver *resolver)
{
	DBG("resolver %p name %s", resolver, resolver->name);

	resolver_list = g_slist_remove(resolver_list, resolver);
}
