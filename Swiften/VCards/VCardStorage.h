/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include "Swiften/Elements/VCard.h"

namespace Swift {
	class JID;

	class VCardStorage {
		public:
			virtual ~VCardStorage();

			virtual boost::shared_ptr<VCard> getVCard(const JID& jid) const = 0;
			virtual void setVCard(const JID&, boost::shared_ptr<VCard>) = 0;
	};
}
