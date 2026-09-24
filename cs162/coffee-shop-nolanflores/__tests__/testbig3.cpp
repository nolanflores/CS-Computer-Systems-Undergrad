// DO NOT MODIFY THIS FILE! IT'S USED TO TEST YOUR BIG 3 IMPLEMENTATIONS IN
// ISOLATION. YOU CAN RUN IT VIA `make test`.

#include "shop.h"
#include "menu.h"
#include "coffee.h"
#include "order.h"

void test_menu_big_3() {
	menu m;
	coffee c;
	m.add_coffee(c);
	m.add_coffee(c);

	// Copy ctor
	menu m2(m);
	
	// Prepare m3 for AOO
	menu m3;
	m3.add_coffee(c);
	
	// AOO
	m3 = m;

	m3 = m2;
}

void test_shop_big_3() {
	shop s;
	coffee c;
	order o;
	s.add_coffee_to_menu(c);
	s.add_order(o);

	// Copy ctor
	shop s2(s);

	// Prepare s3 for AOO
	shop s3;
	s3.add_order(o);

	// AOO
	s3 = s;
}

int main() {
	test_menu_big_3();
	test_shop_big_3();
}
