#pragma once


//簡易UniquePtr
//std::unique_ptrを使用することをおすすめする。
template<class T>
class UniquePtr{
private:

    T * px;
    //コピーされると多重で削除されるのでコピー禁止。
    //ポインタのコピーが発生して、共有する必要がある場合は
    //shared_ptrを使用する
    UniquePtr(UniquePtr const &);
    UniquePtr & operator=(UniquePtr const &);

    void operator==( UniquePtr const& ) const;
    void operator!=( UniquePtr const& ) const;

public:

 	UniquePtr( T * p = 0 ): px( p )
    {
    }

	//デストラクタ。
    ~UniquePtr() // never throws
    {
		delete px;
    }
	//リセット。
    void reset(T * p = 0)
    {
		px = p;
    }

	//*演算子をオーバーロード。
    T & operator*() const 
    {
        return *px;
    }
    //アロー演算子をオーバーロード。
    T * operator->() const
    {
        return px;
    }

	//生ポインタを取得。
    T * get() const 
    {
        return px;
    }

};