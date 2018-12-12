#pragma once
#include <map>
#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>
#include <memory>
#include <algorithm>

namespace rtmp {

const std::size_t kMAXChunkSize = 128;

class Session;
class ChunkStream;
class MessageStream;
class Message;
class ChunkData;
class Header;

typedef boost::shared_ptr<Header> rtmpheader_ptr;
typedef boost::shared_ptr<Session> session_ptr;
typedef boost::shared_ptr<ChunkStream> chunkstream_ptr;
typedef boost::shared_ptr<MessageStream> messagestream_ptr;
typedef boost::shared_ptr<Message> message_ptr;
typedef boost::shared_ptr<ChunkData> chunkdata_ptr;
typedef boost::shared_ptr<unsigned char> char_ptr;

template<typename T, typename Item>
T new_item(unsigned id) {
  T item= T(new Item);
  item->set_id(id);
  return item;
}

template<typename T>
void remove_item(std::map<unsigned,T> items, unsigned id) {
  auto it = items.find(id);
  if (it != items.end())
      items.erase (it);
}
template<typename T>
void add_item(std::map<unsigned,T> items, unsigned id, T item) {
  auto it = items.find(id);
  if (it == items.end())
    items[id] = item;
}

template<typename T, typename Item>
T get_item(std::map<unsigned,T> items, unsigned id) {
  auto it = items.find(id);
  if (it != items.end()) 
    return items[id];

  T item= T(new Item);
  item->set_id(id);
  items[id] = item;

  //T item= new_item<T, Item>(id);
  //add_item<T>(items, id, item);

  return item;
}

class Header{
public:  
  unsigned timestamp_{0};
  std::size_t length_{0};
  unsigned type_id_{0};
  unsigned chunk_stream_id{0};
};

class ChunkData{
public:
  std::vector<unsigned char> data_;
};

class Message {
public:
  unsigned timestamp_{0};
  std::size_t length_{0};
  unsigned type_id_{0};
  std::size_t received_length_{0};
 
  //char_ptr chunk_data_;
  unsigned char* chunk_data_{nullptr};
  ~Message() { 
    //RTMPLOGF(debug, "Message[%1%],chunk_data_[%2%]", this, chunk_data_);
    if (chunk_data_) delete []chunk_data_; 
  }

  std::list<chunkdata_ptr>chunk_datas_;
};

class MessageStream {
public:  
  unsigned id_;
  message_ptr message_;

  ~MessageStream() {
    //RTMPLOGF(debug, "MessageStream[%1%],message_[%2%]", this, message_.get());
  }

  message_ptr new_message() { 
    message_ = message_ptr(new Message); 
    return message_; 
  }
  message_ptr get_current_message() { return message_; };
  void set_current_message(message_ptr message) { message_ = message; };
  void set_id(unsigned id) { id_ = id; }
};

class ChunkStream {
public:  
  unsigned id_;
  std::map<unsigned, messagestream_ptr> message_streams_;
  rtmpheader_ptr preceding_chunk_header_;

  ChunkStream() {
    //RTMPLOGF(debug,"ChunkStream[%1%],header[%2%]", this, preceding_chunk_header_.get());
  }
  ~ChunkStream() {
    //RTMPLOGF(debug,"ChunkStream[%1%],header[%2%]", this, preceding_chunk_header_.get());
  }
  ChunkStream(const ChunkStream& other) {
    preceding_chunk_header_ = other.preceding_chunk_header_;
    //RTMPLOGF(debug,"ChunkStream[%1%],header[%2%]", this, preceding_chunk_header_.get());
  }
  ChunkStream& operator=(const ChunkStream& other) {
    if(&other == this) return *this;    
    preceding_chunk_header_= other.preceding_chunk_header_;
    //RTMPLOGF(debug,"ChunkStream[%1%],header[%2%]", this, preceding_chunk_header_.get());
    return *this;
  }


  void set_id(unsigned id) { id_ = id; }
  rtmpheader_ptr preceding_chunk_header() {
    //RTMPLOGF(debug,"ChunkStream[%1%],header[%2%]", this, preceding_chunk_header_.get());
    return preceding_chunk_header_;
  }
  void set_preceding_chunk_header(rtmpheader_ptr preceding_header) {
    preceding_chunk_header_= preceding_header;
    //RTMPLOGF(debug,"ChunkStream[%1%],header[%2%]", this, preceding_chunk_header_.get());
  }
  messagestream_ptr get_message_stream(unsigned message_stream_id) { 
    return get_item<messagestream_ptr, MessageStream>(message_streams_,message_stream_id);
  }
};

class Session {
public:
  unsigned id_;
  std::map<unsigned, chunkstream_ptr> chunk_streams_;
  std::size_t max_chunk_size_{kMAXChunkSize};

  Session() {
    //RTMPLOGF(debug, "Session[%1%], ChunkStream[%2%]", this, chunk_stream_.get());
  }
  ~Session() {
    //RTMPLOGF(debug,"Session[%1%],chunk_stream_[%2%]", this, chunk_stream_.get());
  }
  Session(const Session& other) {
    chunk_streams_= other.chunk_streams_;
    //RTMPLOGF(debug,"Session[%1%],chunk_stream_[%2%]", this, chunk_stream_.get());
  }
  Session& operator=(const Session& other) {
    if(&other == this) return *this;    
    chunk_streams_= other.chunk_streams_;
    //RTMPLOGF(debug,"Session[%1%],chunk_stream_[%2%]", this, chunk_stream_.get());
    return *this;
  }

  void set_id(unsigned id) { id_ = id; }
  
  chunkstream_ptr get_chunk_stream(unsigned id) { 
    //return get_item<chunkstream_ptr, ChunkStream>(chunk_streams_, id);

    auto it = chunk_streams_.find(id);
    if (it != chunk_streams_.end()) 
    {
      std::cout<<"find" <<std::endl;
      return chunk_streams_[id];
    }

    chunkstream_ptr chunkstream= chunkstream_ptr(new ChunkStream);
    chunkstream->set_id(id);
    chunk_streams_[id] = chunkstream;
    return chunkstream;
  }
};

static std::map<unsigned, session_ptr> sessions_;

inline void remove_session(std::map<unsigned, session_ptr> sessions, unsigned id) {
  remove_item<session_ptr>(sessions, id);
}
inline void add_session(std::map<unsigned, session_ptr> sessions, session_ptr session) {
  add_item<session_ptr>(sessions, session->id_, session);
}
inline session_ptr get_session(std::map<unsigned, session_ptr> sessions, unsigned id) {
  return get_item<session_ptr, Session>(sessions ,id);
}

} // rtmp