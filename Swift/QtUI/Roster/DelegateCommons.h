/*
 * Copyright (c) 2010 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <QApplication>
#include <QFont>

namespace Swift {
	class DelegateCommons {
		public:
			DelegateCommons() : nameFont(QApplication::font()), detailFont(QApplication::font()) {
				detailFontSizeDrop = nameFont.pointSize() >= 10 ? 2 : 0;
				detailFont.setStyle(QFont::StyleItalic);
				detailFont.setPointSize(nameFont.pointSize() - detailFontSizeDrop);
			}

			int detailFontSizeDrop;
			QFont nameFont;
			QFont detailFont;
			static const int horizontalMargin;
			static const int verticalMargin;
			static const int farLeftMargin;			
	};
}
