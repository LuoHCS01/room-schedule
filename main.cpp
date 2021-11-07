#include "network_flow.h"
#include "data_process.h"

namespace Arrange {

void get_graph(Data* data, Graph* graph, std::string room_name) {
    for (int i = 1; i <= data->num_people; i++) {
        Person person = data->people[i];
        // Source is node #0
        // For person i, create a node #i and connect it with source, capacity num_needed
        graph->edge[0][i] = person.num_time_need[room_name];
        // For person i create 7 nodes #(7 * i + 101) to # (7 * i + 107) and connect them with
        // node #i, capacity 1 if he is available in that day
        for (int j = 1; j <= 7; j++) {
            if (person.if_avail_day[j]) {
                int node = 7 * i + 100 + j;
                graph->edge[i][node] = 1;
            }
        }
        // Create node #(900 + t), representing time slice #t
        // For node #(7 * i + 100 + j) (which represents person i in day j), connect it with 
        // node #(900 + t), if time slice #t is in day j. Capacity if_available
        for (int t = 1; t <= data->num_time_slice_total; t++) {
            if (person.if_available[t]) {
                int node = 7 * i + 100 + data->get_day(t).first;
                graph->edge[node][900+t] = 1;
            }
        }
    }
    // Connect node #(900 + t) with destination (node #999), capacity 1
    for (int t = 1; t <= data->num_time_slice_total; t++) {
        graph->edge[900+t][999] = 1;
    }
    // If there are some time slice #j in day #i that is not available, add it here
    /*
    if (room_name == "205") {
        for (int t = 1; t <= data->num_time_slice_total; t++) {
            if (data->get_day(t) == std::pair<int, int>(i, j)) {
                graph->edge[900+t][999] = 0;
            }
        }
    }
    */
}

void get_result(Data* data, Graph* graph, std::string room_name) {
    // Use flow[7*i+100+j][900+t] to determine whether to get the room
    for (int t = 1; t <= data->num_time_slice_total; t++) {
        for (int i = 1; i <= data->num_people; i++) {
            int node = 7 * i + 100 + data->get_day(t).first;
            if (graph->flow[node][900+t]) {
                data->get[room_name][t] = data->people[i].name;
                data->people[i].if_available[t] = false;
                data->people[i].if_avail_day[data->get_day(t).first] = false;
            }
        }
    }
}

} // namespace Arrange

int main() {
    using namespace Arrange;
    Data* data = new Data();
    data->Read("data.csv");
    Graph* graph = new Graph();
    get_graph(data, graph, "208");
    graph->EdmondsKarp(1000, 0, 999);
    get_result(data, graph, "208");
    graph = new Graph();
    get_graph(data, graph, "205");
    graph->EdmondsKarp(1000, 0, 999);
    get_result(data, graph, "205");
    data->Write("out.csv");
    data->Write_Statistics("stat.csv");
    return 0;
}