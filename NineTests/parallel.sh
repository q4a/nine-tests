TESTS_NAMES=$(rg '\{ "test_' NineTests.c | sed "s/.*,\ //" | sed "s/\ .*//")

echo $TESTS_NAMES
for test in $TESTS_NAMES; do
  ./NineTests $test &
done
