#ifndef core_include_commands_common_h
#define core_include_commands_common_h

namespace power_analyzer::yokogawa::common {
    using cmd_t = const char *;
    inline constexpr cmd_t CAL      = "*CAL?";
    inline constexpr cmd_t CAL_RPD  = "%d";
    inline constexpr cmd_t ESE      = "*ESE";
    inline constexpr cmd_t ESE_QRY  = "*ESE?";
    inline constexpr cmd_t ESE_RPD  = "%d";
    inline constexpr cmd_t ESR      = "*ESR?";
    inline constexpr cmd_t ESR      = "%d";
    inline constexpr cmd_t IDN      = "*IDN?";
    inline constexpr cmd_t IDN_RPD  = "*IDN %c";
    inline constexpr cmd_t OPC      = "*OPC";
    inline constexpr cmd_t OPC_QRY  = "*OPC?";
    inline constexpr cmd_t OPC_RPD  = "%d";
    inline constexpr cmd_t OPT      = "*OPT?";
    inline constexpr cmd_t OPT_RPD  = "%s";
    inline constexpr cmd_t PSC      = "*PSC %d";
    inline constexpr cmd_t PSC_QRY  = "*PSC?";
    inline constexpr cmd_t PSC_RPD  = "%d";
    inline constexpr cmd_t RST      = "*RST";
    inline constexpr cmd_t SRE_SET  = "*SRE %d";
    inline constexpr cmd_t SRE_QRY  = "*SRE?";
    inline constexpr cmd_t SRE_RPD  = "%d";
    inline constexpr cmd_t STB_QRY  = "*STB?";
    inline constexpr cmd_t STB_RPD  = "%d";
    inline constexpr cmd_t TRG      = "*TRG";
    inline constexpr cmd_t TST      = "*TST?";
    inline constexpr cmd_t TST_RPD  = "%d";
    inline constexpr cmd_t WAIT     = "*WAI";
}

#endif // core_include_commands_common_h