#ifndef CONFIG_H_
#define CONFIG_H_

#define label_num 3

struct Config {

  // The number of expected consecutive inferences for each gesture type.
  const int consecutiveInferenceThresholds[label_num] = {15, 12, 10};

  const char* output_message[label_num] = {
        "WING:\n\r"
        "*         *         * \n\r"
        " *       * *       *  \n\r"
        "  *     *   *     *   \n\r"
        "   *   *     *   *    \n\r"
        "    * *       * *     \n\r"
        "     *         *      \n\r",
        "RING:\n\r"
        "          *       \n\r"
        "       *     *    \n\r"
        "     *         *  \n\r"
        "    *           * \n\r"
        "     *         *  \n\r"
        "       *     *    \n\r"
        "          *       \n\r",
        "SLOPE:\n\r"
        "        *        \n\r"
        "       *         \n\r"
        "      *          \n\r"
        "     *           \n\r"
        "    *            \n\r"
        "   *             \n\r"
        "  *              \n\r"
        " * * * * * * * * \n\r"};
};

Config config;
#endif // CONFIG_H_
