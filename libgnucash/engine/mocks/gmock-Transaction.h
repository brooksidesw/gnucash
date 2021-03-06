#ifndef GMOCK_TRANSACTION_H
#define GMOCK_TRANSACTION_H

#include <gmock/gmock.h>

#include <Transaction.h>
#include <TransactionP.h>

#include "gmock-qofbook.h"
#include "gmock-gobject.h"


GType gnc_mock_transaction_get_type(void);

#define GNC_TYPE_MOCK_TRANSACTION   (gnc_mock_transaction_get_type ())
#define GNC_IS_MOCK_TRANSACTION(o)  (G_TYPE_CHECK_INSTANCE_TYPE ((o), GNC_TYPE_MOCK_TRANSACTION))


// mock up for Transaction
class MockTransaction : public Transaction
{
public:
    MockTransaction()
    {
        num                 = nullptr;
        description         = nullptr;
        common_currency     = nullptr;
        splits              = nullptr;
        date_entered        = 0;
        date_posted         = 0;
        marker              = 0;
        orig                = nullptr;
        readonly_reason     = nullptr;
        reason_cache_valid  = FALSE;
        isClosingTxn_cached = -1;
    }
    void* operator new(size_t size)
    {
        return mock_g_object_new (GNC_TYPE_MOCK_TRANSACTION, NULL, size);
    }

    // define separate free() function since destructor is protected
    void free()
    {
        delete this;
    }
    void operator delete(void* trans, size_t size)
    {
        mock_g_object_unref(trans, size);
    }

    MOCK_METHOD0(beginEdit, void());
    MOCK_METHOD0(commitEdit, void());
    MOCK_METHOD1(getSplit, Split *(int));
    MOCK_METHOD0(getSplitList, SplitList *());
    MOCK_METHOD1(findSplitByAccount, Split *(const Account*));
    MOCK_METHOD0(getDate, time64());
    MOCK_METHOD1(setDatePostedSecsNormalized, void(time64));
    MOCK_METHOD0(getDescription, const char *());
    MOCK_METHOD1(setDescription, void(const char*));
    MOCK_METHOD0(getNotes, const char *());
    MOCK_METHOD1(setNotes, void(const char*));
    MOCK_METHOD0(getImbalanceValue, gnc_numeric());
    MOCK_METHOD0(getNum, const char *());
    MOCK_METHOD0(isOpen, gboolean());
    MOCK_METHOD0(destroy, void());

protected:
    // Protect destructor to avoid MockTransaction objects to be created on stack. MockTransaction
    // objects can only be dynamically created, since they are derived from GObject.
    ~MockTransaction() {}
};

#endif
