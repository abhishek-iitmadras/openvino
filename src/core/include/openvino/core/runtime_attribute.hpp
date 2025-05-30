// Copyright (C) 2018-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <map>
#include <string>

#include "openvino/core/core_visibility.hpp"
#include "openvino/core/node_vector.hpp"
#include "openvino/core/rtti.hpp"
#include "openvino/core/type.hpp"

namespace ov {
class Node;
class AttributeVisitor;
class Any;

class OPENVINO_API RuntimeAttribute {
public:
    OPENVINO_RTTI_BASE("RuntimeAttribute")

    using Ptr = std::shared_ptr<RuntimeAttribute>;
    using Base = std::tuple<::ov::RuntimeAttribute>;
    virtual ~RuntimeAttribute();
    virtual bool is_copyable() const;
    virtual bool is_copyable(const std::shared_ptr<Node>& to) const;
    /**
     * @brief If attribute is deterministic it should be included in cache hash computation.
     *
     * @return true if deterministic otherwise false.
     */
    virtual bool is_deterministic() const;
    virtual Any init(const std::shared_ptr<Node>& node) const;
    virtual Any merge(const ov::NodeVector& nodes) const;
    virtual Any merge(const ov::OutputVector& outputs) const;
    virtual std::string to_string() const;
    virtual bool visit_attributes(AttributeVisitor&);
    bool visit_attributes(AttributeVisitor& visitor) const {
        return const_cast<RuntimeAttribute*>(this)->visit_attributes(visitor);
    }
};
OPENVINO_API std::ostream& operator<<(std::ostream& os, const RuntimeAttribute& attrubute);

}  // namespace ov
