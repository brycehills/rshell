file(GLOB rshell_test_src
	"*.h"
	"*.cpp"
)

add_executable(test ${rshell_test_src})
TARGET_LINK_LIBRARIES(test gtest)

