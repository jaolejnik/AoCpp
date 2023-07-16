#include "../utils/io.h"

#include <iostream>
#include <unordered_map>

typedef std::unordered_map<std::string, uint16_t> WireSignals;

struct WireConnection
{
    StringVector inputs;
    std::string output = "";
    std::string gate = "";
};

std::vector<WireConnection> prepare_wires(const StringVector2D &instructions)
{
    std::vector<WireConnection> wires;

    for (const auto &instruction : instructions)
    {
        WireConnection wc;
        switch (instruction.size())
        {
        case 3:
        {
            wc.inputs.push_back(instruction[0]);
            break;
        }
        case 4:
        {
            wc.gate = instruction[0]; //"NOT";
            wc.inputs.push_back(instruction[1]);
            break;
        }
        case 5:
        {
            wc.inputs.push_back(instruction[0]);
            wc.gate = instruction[1];
            wc.inputs.push_back(instruction[2]);
            break;
        }
        }

        wc.output = instruction.back();

        wires.push_back(wc);
    }

    return wires;
}

const WireConnection *get_wire_with_output(const std::vector<WireConnection> &connections, const std::string &out)
{
    for (auto wireIter = connections.begin(); wireIter != connections.end(); wireIter++)
    {
        if (wireIter->output == out)
            return &*wireIter;
    }

    return nullptr;
}

uint16_t calculate_wire_signal(const WireConnection &wire, const std::vector<WireConnection> &connections, WireSignals &signals)
{
    if (signals.find(wire.output) != signals.end())
        return signals[wire.output];

    std::vector<uint16_t> in_signals;

    for (const auto &in : wire.inputs)
    {
        try
        {
            in_signals.push_back(std::stoi(in));
        }
        catch (const std::exception &e)
        {
            if (signals.find(in) == signals.end())
                signals[in] = calculate_wire_signal(*get_wire_with_output(connections, in), connections, signals);

            in_signals.push_back(signals[in]);
        }
    }

    if (wire.gate == "NOT")
        return ~in_signals[0];
    else if (wire.gate == "LSHIFT")
        return in_signals[0] << in_signals[1];
    else if (wire.gate == "RSHIFT")
        return in_signals[0] >> in_signals[1];
    else if (wire.gate == "AND")
        return in_signals[0] & in_signals[1];
    else if (wire.gate == "OR")
        return in_signals[0] | in_signals[1];

    return in_signals[0];
}

uint16_t part1(const std::vector<WireConnection> &connections)
{
    WireSignals signals;

    for (const auto &wire : connections)
        signals[wire.output] = calculate_wire_signal(wire, connections, signals);

    return signals["a"];
}

uint16_t part2(const std::vector<WireConnection> &connections, uint16_t a_part1)
{
    WireSignals signals;
    signals["b"] = a_part1;

    for (const auto &wire : connections)
        signals[wire.output] = calculate_wire_signal(wire, connections, signals);

    return signals["a"];
}

int main()
{
    auto input = read_input_2D_vector_string(__FILE__, ' ');
    auto connections = prepare_wires(input);
    auto a_part1 = part1(connections);

    std::cout << "Part 1: " << a_part1 << "\n";
    std::cout << "Part 2: " << part2(connections, a_part1) << "\n";

    return 0;
}
