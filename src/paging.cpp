#include "paging.hpp"

paging::paging(int number_of_pages,int number_of_fast_pages,int organization_type){
    m_number_of_fast_pages = number_of_fast_pages;
    m_number_of_pages = number_of_pages;
    m_fast_pages.resize(number_of_fast_pages,0);
    m_organization_type = organization_type;

    switch (organization_type){
    case 0://FIFO
        break;
    case 1://FWF
        break;
    case 2://LRU
        break;
    case 3://LFU
        m_pages_frequency.resize(number_of_pages,0);
        break;
    case 4:{//RAND
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        rng = std::mt19937(static_cast<unsigned>(seed));
        dist = std::uniform_real_distribution<float>(0,1);
        break;
    }
    case 5:{//RMA
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        rng = std::mt19937(static_cast<unsigned>(seed));
        dist = std::uniform_real_distribution<float>(0,1);
        m_marks_vector.resize(number_of_pages,false);
        m_marks_counter = 0;
        break;
    }
    default:
        break;
    }
    
}
int paging::access(int value){
    int result = -1;
    // std::cout<<
    for(int i =0;i<m_fast_pages.size();i++){
        if (m_fast_pages.at(i) == value){
            if(m_organization_type==5){m_marks_vector.at(i)=true;}
            if(m_organization_type==2){
                m_fast_pages.erase(m_fast_pages.begin()+i);
                m_fast_pages.push_back(value);
            }
            result = 0;
            break;
        }
        if(m_fast_pages.at(i) == 0){
            m_fast_pages.at(i) = value;
            if(m_organization_type==5){m_marks_vector.at(i)=true;}
            if(m_organization_type==2){
                m_fast_pages.erase(m_fast_pages.begin()+i);
                m_fast_pages.push_back(value);
            }
            result = 1;
            break;
        } 
    }
    // logika wyrzucania
    if (result==-1){ 
        switch (m_organization_type){
        case 0://FIFO
            m_fast_pages.erase(m_fast_pages.begin());
            m_fast_pages.push_back(value);
            result = 1;
            break;
        case 1://FWF
            std::fill(m_fast_pages.begin(),m_fast_pages.end(),0);
            m_fast_pages.at(0)=value;
            result = 1;
            break;
        case 2:{//LRU
            // int max_val=-1;
            // int max;
            // for (int i =0; i < m_number_of_fast_pages;i++){
            //     if (m_timestamps.at(m_fast_pages.at(i)-1)>max_val) {
            //         max_val = m_timestamps.at(m_fast_pages.at(i)-1);
            //         max = i;
            //     }
            // }
            m_fast_pages.erase(m_fast_pages.begin());
            m_fast_pages.push_back(value);
            result = 1;
            break;
        }
        case 3:{//LFU
            int min_val =INT32_MAX;
            int min;
            for (int i=0;i<m_number_of_fast_pages;i++){
                if(m_pages_frequency.at(m_fast_pages.at(i)-1)<min_val){
                    min_val = m_pages_frequency.at(m_fast_pages.at(i)-1);
                    min = i;
                }
            }
            m_fast_pages.erase(m_fast_pages.begin()+min);
            m_fast_pages.push_back(value);
            result = 1;
            break;
        }
        case 4://RAND
            m_fast_pages.erase(m_fast_pages.begin()+ceilf(m_number_of_fast_pages*dist(rng)));
            m_fast_pages.push_back(value);
            result = 1;
            break;
        case 5:{//RMA
            int random = ceilf((m_number_of_fast_pages - m_marks_counter)*dist(rng));
            for (int i=0;i<m_number_of_fast_pages;i++){
                if (m_marks_vector.at(i)==0){
                    random--;
                    if (random==0){
                        m_fast_pages.erase(m_fast_pages.begin()+i);
                        m_fast_pages.push_back(value);
                        m_marks_vector.erase(m_marks_vector.begin()+i);
                        m_marks_vector.push_back(true);
                    }
                }
            }
            result = 1;
            break;
        }
        default:
            break;
        }
    }
    //edycja struktur pomocniczych
    switch (m_organization_type){
        case 0://FIFO
            break;
        case 1://FWF
            break;
        case 2://LRU
            break;
        case 3://LFU
            m_pages_frequency.at(value-1)++;
            break;
        case 4://RAND
            break;
        case 5://RMA
            m_marks_counter++;
            if(m_marks_counter==m_number_of_fast_pages){
                std::fill(m_marks_vector.begin(),m_marks_vector.end(),false);
                m_marks_counter=0;
            }
            break;
        default:
            break;
    }

    
    return result;
}
void paging::print(){
    for(int i =0;i<m_number_of_fast_pages;i++){
        std::cout<<m_fast_pages.at(i)<<" ";
    }
    std::cout<<std::endl;
}